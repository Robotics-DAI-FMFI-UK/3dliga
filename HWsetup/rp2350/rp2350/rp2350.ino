// treba si nainštalovať knižnicu Adafruit NeoPixel
#include <Adafruit_NeoPixel.h>

#define PIN        16       
#define NUMPIXELS  1      

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin(); 
  pixels.clear(); 
}

void loop() {
  Serial.print("Ahoj ");
  Serial.println(rand() % 10);
  for (int i = 0; i < 80; i++)
  {
    pixels.setPixelColor(0, pixels.Color(80 - i, i, 0));
    pixels.show();   
    delay(5);
  }
  for (int i = 0; i < 80; i++)
  {
    pixels.setPixelColor(0, pixels.Color(9, 80 - i, i));
    pixels.show();   
    delay(5);
  }
  for (int i = 0; i < 80; i++)
  {
    pixels.setPixelColor(0, pixels.Color(i, 0, 80 - i));
    pixels.show();   
    delay(5);
  }
}
