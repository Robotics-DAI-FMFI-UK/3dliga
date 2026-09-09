#include <EEPROM.h>

void setup() {
  EEPROM.begin(256);

  for (int i = 0; i < 256; i++) {
    EEPROM.write(i, 0);   // 0 používame ako "prázdnu" hodnotu
  }
  EEPROM.commit();        // bez tohto sa vynulovanie neuloží natrvalo

  Serial.begin(115200);
  Serial.println("Pamäť vynulovaná.");
}

void loop() {
}
