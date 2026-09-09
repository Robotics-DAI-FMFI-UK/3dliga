const int MIC_DIGITAL = 5;   // digitálny výstup D0
const int MIC_ANALOG  = 26;  // analógový výstup A0 (ADC)

void setup() {
  pinMode(MIC_DIGITAL, INPUT);
  Serial.begin(9600);
  analogReadResolution(12);
}

void loop() {
  int digitalVal = digitalRead(MIC_DIGITAL);  // 0 alebo 1
  int analogVal  = analogRead(MIC_ANALOG);    // 0 až 4095

  Serial.print("Digitálny: ");
  Serial.print(digitalVal);
  Serial.print("  |  Analógový: ");
  Serial.println(analogVal);

  delay(50);
}

