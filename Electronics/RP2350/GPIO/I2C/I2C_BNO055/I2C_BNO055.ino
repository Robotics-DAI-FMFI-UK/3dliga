#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(115200);
  Wire.setSDA(4);
  Wire.setSCL(5);
  Wire.begin();

  // RP2350 posle adresu (0x28) BNO055 a chce od neho citat data (read/write bit = 1)
  if (!bno.begin()) { // ak BNO055 odpovie, stiahne SDA na LOW (ACK); ak nie, zostane HIGH (NACK)
    Serial.println("BNO055 nenájdený!");
    while (1); // ziadne zariadenie s touto adresou neodpovedalo
  }

  delay(1000);
  bno.setExtCrystalUse(true);
  Serial.println("BNO055 OK");
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event); // kniznica poziada o registre a precita viacero 8-bitovych ramov, kazdy s ACK

  Serial.print("X: ");
  Serial.print(event.orientation.x);
  Serial.print("  Y: ");
  Serial.print(event.orientation.y);
  Serial.print("  Z: ");
  Serial.println(event.orientation.z);

  delay(200);
}
