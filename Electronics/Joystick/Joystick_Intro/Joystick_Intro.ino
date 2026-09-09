const int JOY_X  = 26;
const int JOY_Y  = 27;
const int JOY_SW = 6;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 12-bitové ADC (0–4095)
  pinMode(JOY_SW, INPUT_PULLUP);  // tlačidlo – aktívne LOW
}

void loop() {
  int x  = analogRead(JOY_X);
  int y  = analogRead(JOY_Y);
  int sw = digitalRead(JOY_SW);  // 0 = stlačené, 1 = nestlačené

  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  SW: "); Serial.println(sw == LOW ? "stlacene" : "volne");

  delay(100);
}