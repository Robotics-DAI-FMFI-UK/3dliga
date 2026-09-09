const int TRIG = 6;
const int ECHO = 7;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

// Funkcia odošle impulz a vráti nameraný čas v mikrosekundách
long measurePulse() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH);
}

void loop() {
  long trvanie = measurePulse();

  Serial.print("Čas: ");
  Serial.print(trvanie);

  delay(100);
}