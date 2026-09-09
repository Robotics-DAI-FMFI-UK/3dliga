const int PIN_VRX = 26;
const int PIN_VRY = 27;

void setup() {
  Serial.begin(115200);
}

void loop() {
  int hodnotaX = analogRead(PIN_VRX);
  int hodnotaY = analogRead(PIN_VRY);

  Serial.print("VRX: ");
  Serial.print(hodnotaX);
  Serial.print("  VRY: ");
  Serial.println(hodnotaY);

  delay(200);
}

