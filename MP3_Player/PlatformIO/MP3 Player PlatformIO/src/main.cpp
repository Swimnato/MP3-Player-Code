#include "main.hpp"
#include <SPI.h>
#include <Arduino.h>
#include "PinConfig.hpp"
#include "UI.hpp"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "InputManager.hpp"

InputManager mainInput = InputManager();
FileHandler fileHandler = FileHandler(); 
UI ui = UI(fileHandler, &mainInput);
#define DEBUG_PRINTS true
void setup() {
  // put your setup code here, to run once:
  #if DEBUG_PRINTS
  Serial.begin(9600);
  Serial.println("Starting MP3 Player");
  #endif

  mainInput.init();

  #if DEBUG_PRINTS
  Serial.println("Input Initialized");
  #endif

  

  #if DEBUG_PRINTS
  Serial.println("Screen Initialized");
  #endif

  ui.open_home_menu();
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

  
  ui.update();
}
