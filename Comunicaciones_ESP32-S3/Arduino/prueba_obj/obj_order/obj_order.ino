#include "target.h"
#include "box.h"
#include "container.h"
#include "order.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  target p1 = target(10,15,40);
  box b1 = box("S", p1);
  container c1 = container(1,"000");
  c1.add_box(b1);
  order o1 = order(2, "110");
  o1.add_container(c1);
  Serial.println(b1.ID);
  Serial.println(b1.pos.x);
  Serial.println(b1.pos.y);
  Serial.println(b1.pos.z);
  Serial.println(c1.ID);
  Serial.println(c1.boxes[0].ID);
  Serial.println(o1.ID);
  Serial.println(o1.containers[0].ID);

  //Serial.println(p1.get_x);
  //Serial.println("(%d,%d,%d)", p1.get_x, p1.get_y, p1.get_z);
  delay(1000);

}
