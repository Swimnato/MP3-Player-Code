#ifndef PINCONFIG_H
#define PINCONFIG_H

#define ESP_MOSI  23
#define ESP_MISO  19
#define ESP_SCK   18

#define SCREEN_DC 2
#define SCREEN_CS 4
#define SCREEN_BL 25

#define DETECT_JACK 12
#define GAIN 26
#define DAC_DIN  13
#define DAC_BCLK 14
#define DAC_LRC  15

#define HOLD 17
#define HOME_BUTTON       32
#define BACK_BUTTON       33
#define PLAY_PAUSE_BUTTON 35 
#define MENU_BUTTON       34

#define MOTOR_DRIVER 22

#define VOLUME_ROTARY_ENC_A     16
#define VOLUME_ROTARY_ENC_B     26 // we need to relocate this pin it is really 27 but it constantly resets when we use it
#define ROTARY_ENC_BUTTON 0


#endif