const int PIN_LED_R = 10; // uprav podla realneho zapojenia
const int PIN_LED_G = 11;
const int PIN_LED_B = 12;

void nastav_farbu(int r, int g, int b) {
  analogWrite(PIN_LED_R, r);
  analogWrite(PIN_LED_G, g);
  analogWrite(PIN_LED_B, b);
}

void setup() {
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
}

void loop() {
  // plynuly prechod z cervenej do zelenej
  for (int i = 0; i <= 255; i++) {
    nastav_farbu(255 - i, i, 0);
    delay(5);
  }
  // zo zelenej do modrej
  for (int i = 0; i <= 255; i++) {
    nastav_farbu(0, 255 - i, i);
    delay(5);
  }
  // z modrej spat do cervenej
  for (int i = 0; i <= 255; i++) {
    nastav_farbu(i, 0, 255 - i);
    delay(5);
  }
}