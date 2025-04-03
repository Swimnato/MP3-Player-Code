#include "InputManager.hpp"


//debounce time in ms
#define debounce 10 
bool InputManager::debounceButton(byte buttonIndex) {
  if(buttonStatus[buttonIndex]){
    if(millis() - buttonPressed[buttonIndex] > debounce){
      return true;
    }
  }
  return false;
}
void InputManager::init() {
  for(short i = 0; i < 5; i++){
    pinMode(inputPins[i], INPUT_PULLDOWN);
  }
}

void InputManager::update() {
  for(short i = 0; i < 5; i++){
    bool isPressed = digitalRead(inputPins[i]);
    if(isPressed && !buttonStatus[i]){
      buttonPressed[i] = millis();
    } else if(!isPressed){
      buttonPressed[i] = 0;
    }
    buttonStatus[i] = isPressed;
  }
}

short InputManager::getTurnAmount() {
  uint32_t wheel_position = volWheel.read();
  int16_t amount = (wheel_position - lastWheelPosition) / PULSES_PER_CLICK;
  lastWheelPosition = amount; 
  
  return amount;
}

bool InputManager::isHomePressed() {
  return debounceButton(0);
}

bool InputManager::isBackPressed() {
  return debounceButton(1);
}

bool InputManager::isPlayPausePressed() {
  return debounceButton(2);
}

bool InputManager::isMenuPressed() {
  return debounceButton(3);
}

bool InputManager::isEncoderPressed() {
  return debounceButton(4);
}