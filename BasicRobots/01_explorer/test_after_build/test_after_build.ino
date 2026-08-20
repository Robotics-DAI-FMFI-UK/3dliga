#include <Servo.h>

// GPIO piny podľa manuálu prieskumníka
const int PIN_SERVO_LAVE    = 4;
const int PIN_SERVO_PRAVE   = 5;
const int PIN_SERVO_STREDNE = 6;
const int PIN_TRIG          = 7;
const int PIN_ECHO          = 8;

const int SERVO_STOP = 90; // "stop" poloha pre 360° servá

Servo servoLave;
Servo servoPrave;
Servo servoStredne;

long nameraj_vzdialenost_cm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long trvanie = pulseIn(PIN_ECHO, HIGH, 30000); // timeout 30ms (~5m)
  if (trvanie == 0) return -1; // nič nenamerané (mimo dosahu / timeout)

  return trvanie / 58; // prevod na cm
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  servoLave.attach(PIN_SERVO_LAVE, 540, 2400);
  servoPrave.attach(PIN_SERVO_PRAVE, 540, 2400);
  servoStredne.attach(PIN_SERVO_STREDNE, 540, 2400);

  servoLave.write(SERVO_STOP);
  servoPrave.write(SERVO_STOP);
  servoStredne.write(90);

  delay(1000);
  Serial.println("Test motorckov a senzora spusteny.");
}

void loop() {
  // Test laveho serva - kratke otocenie jednym a druhym smerom
  Serial.println("Test laveho serva...");
  servoLave.write(SERVO_STOP + 30);
  delay(500);
  servoLave.write(SERVO_STOP - 30);
  delay(500);
  servoLave.write(SERVO_STOP);
  delay(500);

  // Test praveho serva
  Serial.println("Test praveho serva...");
  servoPrave.write(SERVO_STOP + 30);
  delay(500);
  servoPrave.write(SERVO_STOP - 30);
  delay(500);
  servoPrave.write(SERVO_STOP);
  delay(500);

  // Test stredneho serva - vychylenie do oboch krajnych poloh
  Serial.println("Test stredneho serva...");
  servoStredne.write(0);
  delay(500);
  servoStredne.write(180);
  delay(500);
  servoStredne.write(90);
  delay(500);

  // Test ultrazvukoveho senzora
  long vzdialenost = nameraj_vzdialenost_cm();
  Serial.print("Namerana vzdialenost: ");
  if (vzdialenost < 0) {
    Serial.println("mimo dosahu");
  } else {
    Serial.print(vzdialenost);
    Serial.println(" cm");
  }

  delay(2000);
}