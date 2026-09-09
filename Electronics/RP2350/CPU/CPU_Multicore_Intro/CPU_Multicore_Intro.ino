// Jadro 0 - hlavna logika (napr. citanie senzorov)
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Jadro 0 bezi...");
  delay(1000);
}

// Jadro 1 - bezi paralelne s jadrom 0 (napr. blikanie LED)
void setup1() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop1() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}
