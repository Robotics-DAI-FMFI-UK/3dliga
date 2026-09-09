#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno;
bool active = false;

void setup() {
  Serial.begin(115200);
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();
  delay(1000);

  // Hľadáme senzor na I2C zbernici
  Serial.println("Hľadám I2C zariadenia...");
  int adresa = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Nájdené zariadenie na adrese: 0x");
      Serial.println(addr, HEX);
      adresa = addr;
    }
  }

  if (adresa > 0) {
    bno = Adafruit_BNO055(55, adresa, &Wire);
    if (bno.begin()) {
      active = true;
      Serial.println("BNO055 OK – čakám na kalibráciu...");
    } else {
      Serial.println("BNO055 begin() zlyhalo");
    }
  } else {
    Serial.println("Žiadny senzor nenájdený!");
  }
}

void loop() {
  if (!active) {
    Serial.println("Senzor nie je pripravený");
    delay(1000);
    return;
  }

  // Kontrola kalibrácie – hodnoty 0-3, kde 3 = plne kalibrované
  uint8_t system, gyro, accel, mag;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  if (system < 1) {
    Serial.println("Kalibrujem – pohni senzorom...");
    delay(100);
    return;
  }

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Serial.print("X: "); Serial.print(euler.x());
  Serial.print("  Y: "); Serial.print(euler.y());
  Serial.print("  Z: "); Serial.println(euler.z());
  delay(100);
}
