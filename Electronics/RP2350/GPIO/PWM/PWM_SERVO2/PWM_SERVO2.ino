#include <Servo.h>

const int PIN_SERVO = 13;

Servo servo;

void setup() {
  servo.attach(PIN_SERVO, 500, 2500);
}

void loop() {
  for (int t = 500; t <= 2500; t += 10) {
    servo.writeMicroseconds(t);
    delay(15);
  }
  for (int t = 2500; t >= 500; t -= 10) {
    servo.writeMicroseconds(t);
    delay(15);
  }
}