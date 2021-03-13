#include "Adafruit_Si7021.h"
#define BuzzerPin 7
#define ResetPin 6
#define LED 13
Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ResetPin, INPUT);
}

int i = 0;
int ResetPin_state = 0;
//bool stop;
void loop() {
  ResetPin_state = digitalRead(ResetPin);
  while (true) {
    if (sensor.readHumidity() < 50) {
      i++;
      pinMode(LED, HIGH);
      delay(1000);
      pinMode(LED, LOW);
      delay(1000);
      if (i >= 2) {
        Buzz();
      }
    }
  }
  if (sensor.readHumidity() > 60) {
    i++;
    pinMode(LED, HIGH);
    if (i >= 2) {
      Buzz();
    }
  }
}
int Buzz() {
  while(1){
    tone(BuzzerPin, k);
    k = 1000;
    delay(100);
    k = 2000;
   }
  if (ResetPin_state == HIGH){
      noTone(BuzzerPin);
      return 0;
  }
}
