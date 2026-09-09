#include <EEPROM.h>

int adresa = 0;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(256);

  float vzdialenost = 23.5;
  EEPROM.put(adresa, vzdialenost);      // zapíše všetkých sizeof(float) = 4 bajty naraz
  EEPROM.commit();

  adresa += sizeof(float);
  vzdialenost += 10;
  EEPROM.put(adresa, vzdialenost);
  EEPROM.commit();

  float nacitanaHodnota;
  EEPROM.get(adresa, nacitanaHodnota);  // prečíta správny počet bajtov automaticky

  Serial.print("Načítaná hodnota: ");
  Serial.println(nacitanaHodnota);
}

void loop() {
}
