#include <Servo.h>
#define SERVO_PIN 12

Servo servo;
int position = 90;
//int impulz = 1500;

void setup() {
  Serial.begin(115200);
  servo.attach(SERVO_PIN, 500, 2500);
  servo.write(position);
  //servo.writeMicroseconds(impulz);
  Serial.print("Motor je na pozicii: ");
  Serial.println(servo.read(SERVO_PIN));
}

void loop() {
}
