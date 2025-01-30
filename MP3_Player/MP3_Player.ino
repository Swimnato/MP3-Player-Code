#include <InputManager.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting MP3 Player");

  Adafruit_ST7789 tft = Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1);
  tft.init(240, 320);
  analogWrite(SCREEN_BL, 255);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println("Screen Initialized");
}

void loop() {
  // put your main code here, to run repeatedly:

}
