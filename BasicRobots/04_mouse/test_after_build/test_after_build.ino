#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <VL53L0X.h>    //VL553L0X by Pololu   (testovane s verziou 1.3.1)
#include <Adafruit_BNO055.h>  // testovane s verziou 1.6.4

#define PIN        16       
#define NUMPIXELS  1      

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// GPIO piny podla manualu 
const int PIN_SERVO_LAVE    = 1;
const int PIN_SERVO_PRAVE   = 2;
const int PIN_XSHUT_LAVY    = 8;
const int PIN_XSHUT_PRAVY   = 12;
const int PIN_XSHUT_PREDNY  = 13;

const int SERVO_STOP        = 93;

Servo servoLave;
Servo servoPrave;

VL53L0X meracLavy;
VL53L0X meracPravy;
VL53L0X meracPredny;

const int ADRESA_LAVY = 0x34;
const int ADRESA_PRAVY = 0x36;
const int ADRESA_PREDNY = 0x38;

const int BNO055_ADRESA = 0x29;

Adafruit_BNO055 orientacia(55, BNO055_ADRESA, &Wire);

void zablikaj()
{
  for (int i = 0; i < 7; i++)
  {
    pixels.setPixelColor(0, pixels.Color(30, 30, 30));
    pixels.show();   
    delay(500);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();   
    delay(500);
  }
}
void setup() {
  pixels.begin(); 
  pixels.clear(); 
  Serial.begin(115200);

  pinMode(PIN_XSHUT_LAVY, OUTPUT);
  digitalWrite(PIN_XSHUT_LAVY, HIGH);  // zacneme konfigurovat lavy
  pinMode(PIN_XSHUT_PRAVY, OUTPUT);
  digitalWrite(PIN_XSHUT_PRAVY, LOW);
  pinMode(PIN_XSHUT_PREDNY, OUTPUT);
  digitalWrite(PIN_XSHUT_PREDNY, LOW);

  servoLave.attach(PIN_SERVO_LAVE, 540, 2400);
  servoPrave.attach(PIN_SERVO_PRAVE, 540, 2400);

  servoLave.write(SERVO_STOP);
  servoPrave.write(SERVO_STOP);

  zablikaj();  // pre istotu cakame na seriovy port v arduino IDE

  Wire1.setSDA(6);  // pre istotu nastavenie default pinov I2C1
  Wire1.setSCL(7);  
  Wire1.begin();
  
  // inicializujeme prvy a nastavime mu adresu
  meracLavy.setBus(&Wire1);

  if (!meracLavy.init()) {
    Serial.println("Lavy senzor nenajdeny!");
    while (1);  // zastav program
  }
  meracLavy.setAddress(ADRESA_LAVY);
  meracLavy.setTimeout(500);
  Serial.println("Lavy OK");

  digitalWrite(PIN_XSHUT_PRAVY, HIGH);   // spristupnime pravy na konfiguraciu (lavy uz nekoliduje, je na inej adrese)
  
  // inicializujeme druhy a nastavime mu adresu
  meracPravy.setBus(&Wire1);
  
  if (!meracPravy.init()) {
    Serial.println("Pravy senzor nenajdeny!");
    while (1);  // zastav program
  }
  meracPravy.setAddress(ADRESA_PRAVY);
  meracPravy.setTimeout(500);
  Serial.println("Pravy OK");

  digitalWrite(PIN_XSHUT_PREDNY, HIGH);   // napokon spristupnime predny na konfiguraciu (ostatne dva uz nekoliduju)
  meracPredny.setBus(&Wire1);
  if (!meracPredny.init()) {
    Serial.println("Predny senzor nenajdeny!");
    while (1);  // zastav program
  }

  meracPredny.setAddress(ADRESA_PREDNY);
  meracPredny.setTimeout(500);
  Serial.println("Predny OK");

  delay(100);
  // zacneme merat na vsetkych troch senzoroch
  meracLavy.startContinuous();
  meracPravy.startContinuous();
  meracPredny.startContinuous();

  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  if (!orientacia.begin())
  {
    Serial.println("Nepodarilo sa inicializovat IMU senzor.");
    while (1);
  }

  uint8_t system, gyro, accel, mag;
  do {
    orientacia.getCalibration(&system, &gyro, &accel, &mag);
    if (system != 3) {
      Serial.println("Kalibracia IMU...");
      delay(100);
    }
  } while (system != 3);

  Serial.println("Senzory inicializovane, poloz robota, spustam test motorov...");
  delay(5000);
}

void fwd()
{
  servoLave.write(SERVO_STOP + 30);
  servoPrave.write(SERVO_STOP - 30);
}

void bwd()
{
  servoLave.write(SERVO_STOP - 30);
  servoPrave.write(SERVO_STOP + 30);
}

void stop()
{
  servoLave.write(SERVO_STOP);
  servoPrave.write(SERVO_STOP);
}

void right()
{
  servoLave.write(SERVO_STOP + 30);
  servoPrave.write(SERVO_STOP + 30);  
}

void left()
{
  servoLave.write(SERVO_STOP - 30);
  servoPrave.write(SERVO_STOP - 30);  
}

int x = 0;

void loop() 
{
  fwd();
  delay(700);
  bwd();
  delay(700);
  left();
  delay(500);
  right();
  delay(500);
  stop();

  while (1)
  {
      Serial.print(x++);
      Serial.print(": ");
      Serial.print(meracLavy.readRangeContinuousMillimeters());
      if (meracLavy.timeoutOccurred()) Serial.print("TIMEOUT");
      Serial.print(" ");
      Serial.print(meracPredny.readRangeContinuousMillimeters());
      if (meracPredny.timeoutOccurred()) Serial.print("TIMEOUT");
      Serial.print(" ");
      Serial.print(meracPravy.readRangeContinuousMillimeters());
      if (meracPravy.timeoutOccurred()) Serial.print("TIMEOUT");      
      
      imu::Vector<3> euler = orientacia.getVector(Adafruit_BNO055::VECTOR_EULER);
      Serial.print(",   yaw: "); Serial.print(euler.x());
      Serial.print(", pitch: "); Serial.print(euler.y());
      Serial.print(", roll: "); Serial.println(euler.z());
      delay(100);
  }
  
}