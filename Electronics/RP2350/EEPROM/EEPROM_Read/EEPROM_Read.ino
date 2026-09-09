#include <EEPROM.h>

int adresa = 0;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(256);

  byte hodnota = EEPROM.read(adresa);
  Serial.print("Hodnota na adrese 0: ");
  Serial.println(hodnota);
}

void loop() {
}