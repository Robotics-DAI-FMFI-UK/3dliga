const int PIN_SERVO = 13; // uprav podla realneho zapojenia

void poslat_impulz(int trvanie_us) {
  digitalWrite(PIN_SERVO, HIGH);
  delayMicroseconds(trvanie_us);
  digitalWrite(PIN_SERVO, LOW);
}

void setup() {
  pinMode(PIN_SERVO, OUTPUT);
}

void loop() {
  for (int t = 500; t <= 2500; t += 10) {
    poslat_impulz(t);
    delay(20);
  }
  for (int t = 2500; t >= 500; t -= 10) {
    poslat_impulz(t);
    delay(20);
  }
}
