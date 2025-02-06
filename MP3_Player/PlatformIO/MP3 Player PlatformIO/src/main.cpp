#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Encoder.h>
#include <InputManager.h>
#include <I2S.h>

#define DEBUG_PRINTS true

InputManager mainInput = InputManager();

void setup() {
  // put your setup code here, to run once:
  #if DEBUG_PRINTS
  Serial.begin(2000000);
  Serial.println("Starting MP3 Player");
  #endif

  mainInput.init();

  #if DEBUG_PRINTS
  Serial.println("Input Initialized");
  #endif

  Adafruit_ST7789 tft = Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1);
  tft.init(240, 320);
  analogWrite(SCREEN_BL, 255);
  tft.fillScreen(ST77XX_BLACK);

  #if DEBUG_PRINTS
  Serial.println("Screen Initialized");
  #endif
}

void loop() {
  mainInput.update();
  #if DEBUG_PRINTS
  Serial.print("Current Inputs: Home: ");
  Serial.print(mainInput.isHomePressed());
  Serial.print("\tBack: ");
  Serial.print(mainInput.isBackPressed());
  Serial.print("\tPlay/Pause: ");
  Serial.print(mainInput.isPlayPausePressed());
  Serial.print("\tMenu: ");
  Serial.print(mainInput.isMenuPressed());
  Serial.print("\tEncoder Button: ");
  Serial.print(mainInput.isEncoderPressed());
  Serial.print("\tEncoder Rotation Since Last Loop: ");
  Serial.println(mainInput.getTurnAmount());
  #endif
}
