#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "PinConfig.hpp"
#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>

class InputManager{
private:
  const uint8_t inputPins[5] = {HOME_BUTTON, BACK_BUTTON, PLAY_PAUSE_BUTTON, MENU_BUTTON, ROTARY_ENC_BUTTON};
  bool buttonStatus[5] = {0,0,0,0,0};
  unsigned long buttonPressed[5];
  Encoder volWheel = Encoder(VOLUME_ROTARY_ENC_A, VOLUME_ROTARY_ENC_B);
  uint32_t lastWheelPosition;

  bool debounceButton(byte buttonIndex);

public:
  void init();

  void update();

  #define PULSES_PER_CLICK 2
  short getTurnAmount();

  bool isHomePressed();

  bool isBackPressed();

  bool isPlayPausePressed();

  bool isMenuPressed();

  bool isEncoderPressed();

};

#endif