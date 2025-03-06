#include <PinConfig.h>
#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>


//debounce time in ms
#define debounce 10 

class InputManager{
private:
  const uint8_t inputPins[5] = {HOME_BUTTON, BACK_BUTTON, PLAY_PAUSE_BUTTON, MENU_BUTTON, ROTARY_ENC_BUTTON};
  bool buttonStatus[5] = {0,0,0,0,0};
  unsigned long buttonPressed[5];
  Encoder volWheel = Encoder(VOLUME_ROTARY_ENC_A, VOLUME_ROTARY_ENC_B);
  uint32_t lastWheelPosition;

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
    uint32_t wheel_position = volWheel.read();
    int16_t amount = (wheel_position - lastWheelPosition) / PULSES_PER_CLICK;
    lastWheelPosition = amount; 
    
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