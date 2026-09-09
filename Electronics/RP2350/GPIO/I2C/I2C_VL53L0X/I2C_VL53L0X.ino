#include <Wire.h> // kniznica pre I2C komunikaciu
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Serial.begin(115200);
  Wire.setSDA(4);  // nastavenie datoveho pinu
  Wire.setSCL(5);  // nastavenie hodinoveho pinu
  Wire.begin();    // start podmienka pri kazdej komunikacii sa posle automaticky

  // RP2350 posle adresu (0x29) VL53L0X a chce od neho citat data (read/write bit = 1)
  if (!sensor.init()) { // ak zariadenie odpovie, stiahne SDA na LOW (ACK); ak nie, zostane HIGH (NACK)
    Serial.println("Senzor nenájdený!");
    while (1);  // ziadne zariadenie s touto adresou neodpovedalo
  }
  sensor.setTimeout(500);
  sensor.startContinuous(); // ACK prislo, mozu sa zacat posielat data
  Serial.println("VL53L0X OK");
}

void loop() {
  int dist = sensor.readRangeContinuousMillimeters(); // kniznica precita viacero 8-bitovych ramov, kazdy s ACK
  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout!");
  } else {
    Serial.print("Vzdialenosť: ");
    Serial.print(dist);
    Serial.println(" mm");
  }
  delay(100);
  // po kazdej transakcii sa posle stop podmienka, ale kniznica hned zacne dalsiu - preto stale citame nove data
}