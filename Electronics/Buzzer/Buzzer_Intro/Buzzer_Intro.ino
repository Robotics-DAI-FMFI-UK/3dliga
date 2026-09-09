const int BUZZER = 4;

void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}
void playNote(int note)
{
  int halfPeriod = 500000 / note;

  for (int i = 0; i < 10; i++) {
    digitalWrite(BUZZER, HIGH);   
    delayMicroseconds(halfPeriod); 
    digitalWrite(BUZZER, LOW);    
    delayMicroseconds(halfPeriod); 
  }
}

void loop() {
  for (int i = 500; i < 2500; i++) {
    playNote(i);
    Serial.print("Hrám notu: ");
    Serial.println(i);
  }
}