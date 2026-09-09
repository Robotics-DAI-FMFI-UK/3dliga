#include <Servo.h>

const int PIN_SERVO_LAVE    = 10;
const int PIN_SERVO_PRAVE   = 11;

const int SERVO_STOP = 90; // "stop" poloha pre 360° servá

Servo servoLave;
Servo servoPrave;

void setup() {
  pinMode(13, OUTPUT);   // S0
  pinMode(14, OUTPUT);   // S1
  pinMode(15, OUTPUT);   // S2
  
  servoLave.attach(PIN_SERVO_LAVE, 540, 2400);
  servoPrave.attach(PIN_SERVO_PRAVE, 540, 2400);

  servoLave.write(SERVO_STOP);
  servoPrave.write(SERVO_STOP);

  Serial.begin(115200);
  delay(3000);
  Serial.println("are you there?");

  mux_select(0);

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
}

// vyber vstupný kanál 0-7
void mux_select(int i)
{
  digitalWrite(13, i & 1);
  digitalWrite(14, (i & 2) >> 1);
  digitalWrite(15, (i & 4) >> 2);
}

int x = 0;

void loop() {

   Serial.print(x / 100);
   Serial.print((x % 100) / 10);
   Serial.print(x % 10);
   Serial.print(":");

   for (int i = 0; i < 8; i++)
   {
      mux_select(i);             // vyber kanál
      int y = analogRead(27);    // prečítaj hodnotu
      Serial.print(" ");         // zobraz ju
      Serial.print(y /100);
      Serial.print((y % 100) / 10);
      Serial.print(y % 10);
      delay(10);
   }
   Serial.println();
   x++;
   if (x == 999) x = 0;
   delay(300);
}

