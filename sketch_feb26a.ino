#include "Adafruit_Si7021.h"
const int STAT_LED = 10;
#define BuzzerPin 7
#define ResetPin 6
int i = 0;
int ResetPin_state = 0;
bool muted;
Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ResetPin, INPUT);
}


void loop() {
  ResetPin_state = digitalRead(ResetPin);
  while (true) {
    if (sensor.readHumidity() < 50) {
      i++;
      pinMode(STAT_LED, HIGH);
      delay(1000);
      pinMode(STAT_LED, LOW);
      delay(1000);
      if (i >= 2) {
        Buzz();
      }
    }
  }
  if (sensor.readHumidity() > 60) {
    i++;
    pinMode(STAT_LED, HIGH);
    if (i >= 2) {
      Buzz();
    }
  }
}
int Buzz() {
  for (int k = 1000; k != 3000; k += 100) {
    tone(BuzzerPin, k);
    if (ResetPin_state == HIGH) {
      muted = true;
      i = 0;
      k = 1000;
      return 0;
    }
  }
}
