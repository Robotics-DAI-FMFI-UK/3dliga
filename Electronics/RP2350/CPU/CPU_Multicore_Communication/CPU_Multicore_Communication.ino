// Jadro 0 - odosiela data jadru 1
void setup() {
  Serial.begin(115200);
}

void loop() {
  int hodnota = analogRead(A0);     // napr. nacitanie zo senzora
  rp2040.fifo.push(hodnota);        // posli hodnotu jadru 1
  delay(200);
}

// Jadro 1 - prijima data od jadra 0
void setup1() {
}

void loop1() {
  if (rp2040.fifo.available() > 0) {
    int prijataHodnota = rp2040.fifo.pop();
    Serial.print("Jadro 1 prijalo: ");
    Serial.println(prijataHodnota);
  }
}
