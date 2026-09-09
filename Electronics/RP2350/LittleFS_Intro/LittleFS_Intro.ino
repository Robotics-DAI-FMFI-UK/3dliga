#include <LittleFS.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (!LittleFS.begin()) {
    Serial.println("LittleFS sa nepodarilo spustit!");
    return;
  }
  Serial.println("LittleFS pripraveny.");
  //Vytvorenie a zapis suboru
  /*
  File f = LittleFS.open("/data.txt", "w");
  if (f) {
    f.println("Prvy riadok dat");
    f.println("Druhy riadok dat");
    f.close();
    Serial.println("Zapisane.");
  } else {
    Serial.println("Nepodarilo sa otvorit súbor na zapis!");
  }*/

  /* Citanie zo suboru
  File f = LittleFS.open("/data.txt", "r");
  if (f) {
    while (f.available()) {
      Serial.write(f.read());
    }
    f.close();
  } else {
    Serial.println("Súbor neexistuje!");
  }
  */

  //Pridavanie do suboru
  /*
  File f = LittleFS.open("/data.txt", "a");
  if (f) {
    f.println("Dalsi zaznam, ktory sa priplete na koniec");
    f.close();
  }
  */
}

void loop() {
}