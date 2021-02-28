#include "Adafruit_Si7021.h"
// const int LED_BUILTIN = 13;
#define BuzzerPin 7
#define ResetPin 6

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ResetPin, INPUT);
}

int i = 0;
int ResetPin_state = 0;
bool stop;
void loop() {
  ResetPin_state = digitalRead(ResetPin);
  while (true) {
    if (sensor.readHumidity() < 50) {
      i++;
      pinMode(LED_BUILTIN, HIGH);
      delay(1000);
      pinMode(LED_BUILTIN, LOW);
      delay(1000);
      if (i >= 2) {
        Buzz();
      }
    }
  }
  if (sensor.readHumidity() > 60) {
    i++;
    pinMode(LED_BUILTIN, HIGH);
    if (i >= 2) {
      Buzz();
    }
  }
}
int Buzz() {
  for (int k = 1000; k != 3000; k += 100) {
    tone(BuzzerPin, k);
    if (ResetPin_state == HIGH) {
      stop = true;
      i = 0;
      k = 1000;
      return 0;
    }
  }
}
