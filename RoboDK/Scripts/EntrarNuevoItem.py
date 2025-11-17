# Type help("robodk.robolink") or help("robodk.robomath") for more information
# Press F5 to run the script
# Documentation: https://robodk.com/doc/en/RoboDK-API.html
# Reference:     https://robodk.com/doc/en/PythonAPI/robodk.html
# Note: It is not required to keep a copy of this file, your Python script is saved with your RDK project


# Forward and backwards compatible use of the RoboDK API:
# Remove these 2 lines to follow python programming guidelines
from robodk import *      # RoboDK API
from robolink import *    # Robot toolbox
# Link to RoboDK
RDK = Robolink()

MECHANISM_NAME='Cinta'
INCREMENTO_MM=300

#Obtenemos el valor de la variable contador la cual está definida en la estación
#Tened en cuenta ponerla a 0 para reiniciar el funcionamiento
contador=int(RDK.getParam('contador'))
mechanism=RDK.Item(MECHANISM_NAME,itemtype=ITEM_TYPE_ROBOT)
#Este es el objeto que vamos a crear dinámicamente
botella=RDK.Item('Botella')
#Este es el sistema de referencia en el que meteremos el elemento copiado
padre=RDK.Item('Objeto_Cinta')

   

if mechanism.Valid():
    #Avanzamos la cinta
    mechanism.MoveJ(mechanism.Joints()+INCREMENTO_MM)
    #Copiamos el objeto
    botella.Copy()
    #Pegamos el objeto
    botella_copia=RDK.Paste()
    #Lo metemos en el sistema de referencia donde estarán todos los objetos
    botella_copia.setParent(padre)
    #incrementamos la cuenta de objetos copiados
    contador=contador+1
    #Cambiamos la posición del elemento copiado haciendo una traslación que corresponde
    #en el eje X a el número de veces que hemos hecho avanzar ya la cinta
    botella_copia.setPose(transl(-(INCREMENTO_MM)*contador,200,0))
    #hacemos visible el objeto nuevo
    botella_copia.setVisible(1)
    #Actualizamos el valor de la variable contador en la estación
    RDK.setParam('contador',contador)
    

