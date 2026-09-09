const int PIN_TOUCH = 7;

void setup() {
  pinMode(PIN_TOUCH, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int stav = digitalRead(PIN_TOUCH);

  if (stav == LOW) {
    Serial.println("Senzor je aktivovany");
  } else {
    Serial.println("Senzor nie je aktivovany");
  }

  delay(200);
}
