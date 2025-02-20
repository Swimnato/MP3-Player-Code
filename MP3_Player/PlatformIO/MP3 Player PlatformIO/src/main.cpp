#include "main.hpp"
#include <SPI.h>
#include <Arduino.h>
#include "PinConfig.h"
#include "menu.hpp"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "InputManager.h"

InputManager mainInput = InputManager();
Adafruit_ST7789 * tft;
#define DEBUG_PRINTS true
void setup() {
  // put your setup code here, to run once:
  #if DEBUG_PRINTS
  Serial.begin(9600);
  Serial.println("Starting MP3 Player");
  #endif

  //mainInput.init();

  #if DEBUG_PRINTS
  Serial.println("Input Initialized");
  #endif

  tft = new Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1);
  tft->init(240, 320);
  analogWrite(SCREEN_BL, 255);
  clear_display();

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
