#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define PIN        16       
#define NUMPIXELS  1      

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


const int PIN_SERVO_ZAKLADNA = 3;
const int PIN_SERVO_LAVE    = 4;
const int PIN_SERVO_PRAVE   = 5;
const int PIN_SERVO_RUKA = 6;

const int PIN_TOUCH1 = 8;
const int PIN_TOUCH2 = 9;

const int PIN_JOY_SWITCH = 28;
const int PIN_JOY_X = 26;
const int PIN_JOY_Y = 27;

const int SERVO_STOP = 93; // "stop" poloha pre 360° servá

Servo zakladna;
Servo servoLave;
Servo servoPrave;
Servo ruka;

void setup() {
  pixels.begin(); 
  pixels.clear(); 
  pinMode(PIN_TOUCH1, INPUT_PULLUP);
  pinMode(PIN_TOUCH2, INPUT_PULLUP);
  pinMode(PIN_JOY_SWITCH, INPUT_PULLUP);

  Serial.begin(115200);
  delay(5000);
}

void serial_vycisti() {
    while (Serial.available()) 
    {
      Serial.read();
      delay(10);
    }
}

void wait_for_ENTER(const char *sprava = 0)
{
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));
    pixels.show();   

    serial_vycisti();
    unsigned long t1 = millis();
    do { 
        if (sprava)
        {
            if (millis() - t1 > 2000)
            {
                if (sprava) Serial.println(sprava);
                t1 = millis();
            }
        }
        delay(10);
    } while (!Serial.available());
    serial_vycisti();
    
    pixels.setPixelColor(0, pixels.Color(0, 100, 0));
    pixels.show();   
}

void pomaly_pohyb(Servo *s, int poz_zaciatok, int poz_koniec)
{
    int poz = poz_zaciatok;
    while (poz != poz_koniec)
    {
       s->write(poz);
       delay(30);
       if (poz_koniec > poz) poz++;
       else poz--;
    } 
    s->write(poz_koniec);
}

void ln()
{
  Serial.println("------------------------------------------------------------------------------------------------------------");
    
}

void loop() {
    wait_for_ENTER("Ked budes pripraveny, posli ENTER..."); 
    Serial.println("************************************************************************************************************");
    Serial.println("V ziadnom pripade nehyb ziadnym stupnom volnosti rukou, iba z programu. Pri pohybe rukou sa servo poskodi!!!");
    Serial.println("Ak by niektory stupen volnosti zjavne dosiel na svoj koniec a mohol tlacit dalej, treba robot hned vypnut!!!");
    Serial.println("************************************************************************************************************");
    Serial.println("1. Najskor vyskusame zakladnu, ked stlacis ENTER, tak ju pripojim, otocim mierne do jednej aj do druhej strany a zasa odpojim...");
    Serial.println("Ak by otocenie zakladne mohlo sposobit problem, tak nepokracuj dalej, odpoj kabel, robota vypni a priprav ho znovu.");
    wait_for_ENTER();

    zakladna.attach(PIN_SERVO_ZAKLADNA, 540, 2400);
    delay(1000);
    zakladna.write(SERVO_STOP + 8);
    delay(1000);
    zakladna.write(SERVO_STOP - 8);
    delay(1000);
    zakladna.write(SERVO_STOP);
    delay(500);
    zakladna.detach();

    ln();
    Serial.println("2. Teraz vyskusame ruku. Dufam, ze ich mas namontovane tak, ze stredna poloha je pri otvorenej ruke.");
    Serial.println("Ked stlacis ENTER, tak sa servo ruky da do strednej polohy, potom ho otocim o 30 stupnov vlavo a vpravo a zasa odpojim...");
    Serial.println("Ak ruka nie je nenamontovana tak, ze pri 90 stupnoch je otvorena, tak radsej robota vypni.");
    wait_for_ENTER();

    ruka.attach(PIN_SERVO_RUKA, 540, 2400);
    ruka.write(90);
    delay(1000);
    pomaly_pohyb(&ruka, 90, 60);
    delay(1000);
    pomaly_pohyb(&ruka, 60, 120);
    delay(1000);
    pomaly_pohyb(&ruka, 120, 90);
    delay(1000);
    ruka.detach();

    ln();
    Serial.println("3. Otestujeme lave rameno. Po stlaceni ENTER ho pripojim, presuniem do stredu, kusok do jednej strany a kusok do druhej...");
    wait_for_ENTER();
    servoLave.attach(PIN_SERVO_LAVE, 540, 2400);
    servoLave.write(90);
    delay(1000);
    pomaly_pohyb(&servoLave, 90, 110);
    delay(1000);
    pomaly_pohyb(&servoLave, 110, 70);
    delay(1000);
    pomaly_pohyb(&servoLave, 70, 90);
    delay(1000);
    servoLave.detach();

    ln();
    Serial.println("4. Prave rameno. Po stlaceni ENTER ho pripojim, presuniem do stredu, kusok do jednej strany a kusok do druhej...");
    wait_for_ENTER();
    servoPrave.attach(PIN_SERVO_PRAVE, 540, 2400);
    servoPrave.write(90);
    delay(1000);
    pomaly_pohyb(&servoPrave, 90, 105);
    delay(1000);
    pomaly_pohyb(&servoPrave, 105, 75);
    delay(1000);
    pomaly_pohyb(&servoPrave, 75, 90);
    delay(1000);
    servoPrave.detach();

    ln();
    Serial.println("5. Otestujeme dotykove senzory, ked si pripraveny, stlac ENTER...");
    wait_for_ENTER();
    Serial.println("Test bude ukonceny, ked stlacis ENTER...");
    int touch1 = 0;
    int touch2 = 0;
    do {
      if (touch1 != digitalRead(PIN_TOUCH1))
      {
        touch1 ^= 1;
        if (touch1) Serial.println("1 ON");
        else Serial.println("1 OFF");
      }
      if (touch2 != digitalRead(PIN_TOUCH2))
      {
        touch2 ^= 1;
        if (touch2) Serial.println("2 ON");
        else Serial.println("2 OFF");
      }
    } while (!Serial.available());
    serial_vycisti();

    ln();
    Serial.println("6. Otestujeme joystick, ked si pripraveny, stlac ENTER...");
    wait_for_ENTER();
    Serial.println("Test bude ukonceny, ked stlacis ENTER...");
    
    int click = 1;
    int x = -1;
    int y = -1;
    do {
      int novex = analogRead(PIN_JOY_X);
      int novey = analogRead(PIN_JOY_Y);
      if ((abs(x - novex) > 2) || (abs(y - novey) > 2))
      {
        Serial.print("X="); Serial.print(novex / 1000); Serial.print((novex % 1000) / 100); Serial.print((novex % 100) / 10); Serial.print(novex % 10);
        Serial.print(", Y="); Serial.print(novey / 1000); Serial.print((novey % 1000) / 100); Serial.print((novey % 100) / 10); Serial.println(novey % 10);      
        x = novex; y = novey;
      }
      if (click != digitalRead(PIN_JOY_SWITCH))
      {
        click ^= 1;
        if (click) Serial.println("RELEASED");
        else Serial.println("PRESSED");
      }
      delay(200);
    } while (!Serial.available());
    serial_vycisti();

    Serial.println("--------------koniec--------------");
    while (1)
    {
        pixels.setPixelColor(0, pixels.Color(100, 0, 0));
        pixels.show();   
        delay(300);
        pixels.setPixelColor(0, pixels.Color(0, 100, 0));
        pixels.show(); 
        delay(300);  
        pixels.setPixelColor(0, pixels.Color(0, 0, 100));
        pixels.show();
        delay(300);
    }
}
