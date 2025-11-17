from robodk import *
from robolink import *

class target:
    
    position_x = 0
    position_y = 0
    position_z = 0
    ID_box = 0

    def __init__(self, position_x, position_y, position_z):
        self.position_x = position_x
        self.position_y = position_y
        self.position_z = position_z

    def set_ID_box(self, ID_box):
        self.ID_box = ID_box

file_tagets = open('D:\\repos\Automatic_stock\\filesTXT\\results.txt', 'r')
lines = file_tagets.readlines()
containers = {}
boxes = {}
targets = {}
cont_box = 0
cont_target = 0
pos_x = 0
pos_y = 0
pos_z = 0
ID_box = 0
cont_target_vector = 0
targets_vector = []
str_number = ''
coordenadas = ""
contador_target = 0
contador_boxes = 0

for line in lines:
    if line.startswith('Container'):
        container_id = line.split(':')[1].strip()
        containers[container_id] = []
    elif line.startswith('Number-boxes'):
        n_box = int(line.split(':')[1].strip())
        containers[container_id].append({'n_box': n_box}) 
    elif line.startswith('ID_Box'):
        box_id = line.split(':')[1].strip()
        boxes[cont_box] = {box_id}
        cont_box = cont_box + 1
    elif line.startswith('Target'):
        target_id = line.split(':')[1].strip()
        targets[cont_target] = {target_id}
        cont_target = cont_target + 1

for target_id_vector in targets.items():
    coordenadas = str(targets[contador_target]).strip("{'}").strip("()").split(",")
    pos_x = float(coordenadas[0])
    pos_y = float(coordenadas[1])
    pos_z = float(coordenadas[2])
    T1 = target(pos_x, pos_y, pos_z)
    targets_vector.append(T1)
    contador_target = contador_target + 1

for box_id_vector in boxes.items():
    ID_box = str(boxes[contador_boxes]).strip("{'}")
    targets_vector[contador_boxes].set_ID_box(int(ID_box))
    contador_boxes = contador_boxes + 1

for container_id in containers.items():
    print(f"Container ID: {container_id}")
    for box_id in boxes.items():
        print(f"Box ID: {box_id}")
    for target_id in targets.items():
        print(f"Target ID: {target_id}")

# Print the targets
for j in targets_vector:
    print(f"Target ID: {j.ID_box}  - Position: ({j.position_x}, {j.position_y}, {j.position_z})")

file_tagets.close()

RDK = robolink.Robolink()

APPROACH = 100


robot = RDK.Item('UR20', ITEM_TYPE_ROBOT)
AGV = RDK.Item('Omron HD-1500', ITEM_TYPE_ROBOT)
reference = RDK.Item('Pose_ref', ITEM_TYPE_TARGET)
pick = RDK.Item('Target 1', ITEM_TYPE_TARGET)
tool = RDK.Item('Vacuum Gripper', ITEM_TYPE_TOOL)
system_ref = RDK.Item('Frame 3', ITEM_TYPE_FRAME)
target_home = RDK.Item('HOME', ITEM_TYPE_TARGET)
pose_ref = reference.Pose()
pose_pick = pick.Pose()
pose_prepick = pose_pick * transl(0, 0, -20)


def TCP_On(toolitem):
    """Attaches the closest object to the toolitem Htool pose,
    It will also output appropriate function calls on the generated robot program (call to TCP_On)"""
    toolitem.AttachClosest()
    toolitem.RDK().RunMessage('Set air valve on')
    toolitem.RDK().RunProgram('TCP_On()');
        
def TCP_Off(toolitem, itemleave=0):
    """Detaches the closest object attached to the toolitem Htool pose,
    It will also output appropriate function calls on the generated robot program (call to TCP_Off)"""
    toolitem.DetachAll()
    toolitem.RDK().RunMessage('Set air valve off')
    toolitem.RDK().RunProgram('TCP_Off()');

robot.setPoseFrame(system_ref)

robot.MoveJ(target_home)
for target in targets_vector:
    robot.MoveJ(pose_prepick)
    robot.MoveJ(pose_pick)
    TCP_On(tool)
    robot.MoveJ(target_home)
    pose_i = pose_ref * transl((target.position_x * 10), -(target.position_y * 10), -(target.position_z * 10))
    robot.MoveJ(pose_i)
    TCP_Off(tool, system_ref)
    robot.MoveJ(target_home)
    


quit()
