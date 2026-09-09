#include <Wire.h>

const int PIN_SDA = 0;
const int PIN_SCL = 1;

void setup() {
  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.begin();

  Serial.begin(115200);
  delay(1000);
  Serial.println("I2C skener spusteny...");
}

void loop() {
  byte pocetNajdenych = 0;

  for (byte adresa = 1; adresa < 127; adresa++) {
    Wire.beginTransmission(adresa);
    byte chyba = Wire.endTransmission();

    if (chyba == 0) {
      Serial.print("Zariadenie najdene na adrese 0x");
      if (adresa < 16) Serial.print("0");
      Serial.println(adresa, HEX);
      pocetNajdenych++;
    }
  }

  if (pocetNajdenych == 0) {
    Serial.println("Ziadne I2C zariadenie nenajdene.");
  }

  delay(3000);
}
