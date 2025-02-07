#include <PinConfig.h>
#include <Arduino.h>
#include <RotaryEncoder.h>

//debounce time in ms
#define debounce 10 

class InputManager{
private:
  const byte inputPins[5] = {HOME_BUTTON, BACK_BUTTON, PLAY_PAUSE_BUTTON, MENU_BUTTON, ROTARY_ENC_BUTTON};
  bool buttonStatus[5] = {0,0,0,0,0};
  unsigned long buttonPressed[5];
  RotaryEncoder volWheel = RotaryEncoder(VOLUME_ROTARY_ENC_A, VOLUME_ROTARY_ENC_B);
  long lastWheelPosition;

  bool debounceButton(byte buttonIndex){
    if(buttonStatus[buttonIndex]){
      if(millis() - buttonPressed[buttonIndex] > debounce){
        return true;
      }
    }
    return false;
  }

public:

  void init(){
    for(short i = 0; i < 5; i++){
      pinMode(inputPins[i], INPUT);
    }
  }

  void update(){
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

  #define PULSES_PER_CLICK 2
  short getTurnAmount(){
    short amount = (volWheel.getPosition() - lastWheelPosition) / PULSES_PER_CLICK;
    
    lastWheelPosition += amount * PULSES_PER_CLICK;
    
    return amount;
  }

  bool isHomePressed(){
    return debounceButton(0);
  }

  bool isBackPressed(){
    return debounceButton(1);
  }

  bool isPlayPausePressed(){
    return debounceButton(2);
  }

  bool isMenuPressed(){
    return debounceButton(3);
  }

  bool isEncoderPressed(){
    return debounceButton(4);
  }

};