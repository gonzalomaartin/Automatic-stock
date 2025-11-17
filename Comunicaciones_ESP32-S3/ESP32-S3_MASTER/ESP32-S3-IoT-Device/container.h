#include "box.h"

class container : public box {

private:

  String ID;
  box* boxes;
  int nboxes;
  bool set = false;

public:

  container(int nbox, String idcontainer) {
    ID = idcontainer;
    nboxes = nbox;
    boxes = new box[nbox];
    set = false;
  }

  container() {
    ID = "";
    set = false;
  }

  void add_box(box b_add) {
    for (int i = 0; i < nboxes; i++) {
      if (!(boxes[i].get_setBox())) {
        boxes[i] = b_add;
        boxes[i].set_box();
        i = nboxes;
      }
    }
  }

  String get_containerID() {
    return ID;
  }

  box* get_boxes() {
    return boxes;
  }

  int get_containerSize() {
    return nboxes;
  }

  void set_boxes(box* newBoxes) {
    boxes = newBoxes;
  }

  void set_container()
  {
    set = true;
  }

  bool get_setContainer()
  {
    return set;
  }

  void print_container() {
    Serial.print("CONTAINER --> ");
    Serial.println(ID);
    if (ID != "") {
      for (int i = 0; i < nboxes; i++) {
        boxes[i].print_box();
      }
    }
  }
};