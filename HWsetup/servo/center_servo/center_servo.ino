// pripojte servo na pin 14
#include <Servo.h>

Servo s;

void setup() {
  s.attach(14, 544, 2400); 
  delay(2000);
  s.write(5);
  delay(1000);
  s.write(175);
  delay(1000);
  s.write(90);
}

void loop() {
}
