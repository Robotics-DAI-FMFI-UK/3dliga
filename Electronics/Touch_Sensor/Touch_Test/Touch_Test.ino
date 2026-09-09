const int TOUCH_PIN = 7;

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  int val = digitalRead(TOUCH_PIN);

  if (val == HIGH) {
    Serial.println("Dotyk detekovaný!");
  } else {
    Serial.println("Žiadny dotyk");
  }

  delay(100);
}