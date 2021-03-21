/* ---------------------------- Libraries ----------------------------  */
#include <Adafruit_GFX.h>
#include "Adafruit_Si7021.h"
#include <Adafruit_SSD1306.h>
/* ----------------------------- Display Defines ----------------------------- */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK,OLED_DC, OLED_RESET, OLED_CS);
 /* ------------------------------Other Defines and Sensor Init------------------------- */
#define ResetPin 8
#define LED 7
Adafruit_Si7021 sensor = Adafruit_Si7021();
// o7 ,33x35px
const unsigned char odka [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0x00, 0x03, 0xff, 0x80, 0xff, 
	0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 
	0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 
	0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xfb, 0xff, 0x80, 0xff, 0xff, 0xf7, 0xff, 
	0x80, 0xf0, 0x3f, 0xf7, 0xff, 0x80, 0xef, 0x8f, 0xf7, 0xff, 0x80, 0xcf, 0xef, 0xf7, 0xff, 0x80, 
	0xdf, 0xf7, 0xf7, 0xff, 0x80, 0xff, 0xf7, 0xf7, 0xff, 0x80, 0xbf, 0xf7, 0xff, 0xff, 0x80, 0xff, 
	0xf7, 0xff, 0xff, 0x80, 0xff, 0xf7, 0xef, 0xff, 0x80, 0xff, 0xf7, 0xdf, 0xff, 0x80, 0xff, 0xf7, 
	0xdf, 0xff, 0x80, 0xcf, 0xef, 0xdf, 0xff, 0x80, 0xef, 0xdf, 0xdf, 0xff, 0x80, 0xf0, 0x3f, 0xbf, 
	0xff, 0x80, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xff, 0xff, 0xbf, 0xff, 0x80, 0xff, 0xff, 0xbf, 0xff, 
	0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0x80
};
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(ResetPin, INPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; 
  }
  display.clearDisplay();
  display.display();
  delay(2000);
}

void loop() {
  DrawHumidityTempr();
  delay(1000);
}

void DrawHumidityTempr(void) {

  display.clearDisplay();
  /* =================================== */
  // Draws Sensor Temperature
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temperature:"));
  display.print(sensor.readTemperature());
  /* ===================================== */
  // Draws Humidity
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print(sensor.readHumidity());
  display.print(F("%"));
  /* =================================== */
  // Different Humidtiy levels means differrent text at the bottom of the screen
  if (sensor.readHumidity() < 50) {
    display.setCursor(0, 45);
    display.setTextSize(2);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.print(F("LOW"));
  }
  if (sensor.readHumidity() > 55) {
    display.setCursor(0, 45);
    display.setTextSize(2);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.print(F("HIGH"));
  } else if (sensor.readHumidity() == 50) {
    display.setCursor(0, 45);
    display.setTextSize(2);
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    display.println(F("OK"));
  }
  /* =================================== */
  // Some icon so it won't be boring to look at 
   display.drawBitmap(95, 20, odka, 33, 35, WHITE);
  /* =================================== */ 
  display.display();
  delay(1000);
}