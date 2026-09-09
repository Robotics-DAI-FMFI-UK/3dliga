#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  EEPROM.begin(256);      // rezervuje 256 bajtov "EEPROM" priestoru vo flashi (max. 4096)

  EEPROM.write(0, 123);   // zapíše hodnotu 123 na adresu 0
  EEPROM.commit();        // POVINNÉ – reálne zapíše do flashe (inak zostane len v RAM cache)

  byte hodnota = EEPROM.read(0);
  Serial.print("Zapísaná hodnota: ");
  Serial.println(hodnota);
}

void loop() {
}
