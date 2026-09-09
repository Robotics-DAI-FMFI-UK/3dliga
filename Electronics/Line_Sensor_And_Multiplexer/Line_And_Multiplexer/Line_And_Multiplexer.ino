/*
  RP2350                74HC4051             QTR-8A 
┌──────────┐ ┌──────────────────────────┐  ┌────────┐
|      5V  ├─┘        ┌──────────┐      └──┤ IR     |
|      3.3V├──────────┤VCC    VCC├─────────┤ VCC    |
│      GP26├──────────┤Z      GND├─────────┤ GND    | 
│      GP13├──────────┤S2      Y0├─────────┤ D1     |
│      GP14├──────────┤S1      Y1├─────────┤ D2     |
│      GP15├──────────┤S0      Y2├─────────┤ D3     |
│       GND├──────────┤GND     Y3├─────────┤ D4     |
└──────────┘          |        Y4├─────────┤ D5     |
                      |        Y5├─────────┤ D6     |
                      |        Y6├─────────┤ D7     |
                      |        Y7├─────────┤ D8     |
                      └──────────┘         └────────┘
*/
const int MUX_Z  = 26;  // analógový výstup multiplexera
const int MUX_S0 = 6;   // select bit 0
const int MUX_S1 = 7;   // select bit 1
const int MUX_S2 = 8;   // select bit 2

const uint8_t SENSOR_COUNT = 8;
const int THRESHOLD = 400;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 12-bitové ADC (0–4095)

  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);

  Serial.println("QTR-8A + 74HC4051 OK");
}

// Prepne multiplexer na daný kanál (0–7)
void selectChannel(uint8_t channel) {
  digitalWrite(MUX_S0, (channel >> 0) & 1);
  digitalWrite(MUX_S1, (channel >> 1) & 1);
  digitalWrite(MUX_S2, (channel >> 2) & 1);
}

void loop() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    selectChannel(i);
    delayMicroseconds(10);  // počkáme kým sa multiplexer prepne
    int val = analogRead(MUX_Z);
    Serial.print(val > THRESHOLD ? "1" : "0");
    Serial.print("\t");
  }
  Serial.println();
  delay(100);
}
