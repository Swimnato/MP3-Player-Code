#ifndef PINCONFIG_H
#define PINCONFIG_H

#ifdef LOLIN32_LITE
#pragma message "Compiling with LOLIN Pinout!"
#define ESP_MOSI  11
#define ESP_MISO  13
#define ESP_SCK   12

#define SCREEN_DC 9
#define SCREEN_CS 1
#define SCREEN_BL 17

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
#else

#define ESP_MOSI  11
#define ESP_MISO  13
#define ESP_SCK   12

#define SCREEN_DC 9
#define SCREEN_CS 1
#define SCREEN_BL 17

#define DETECT_JACK 3
#define GAIN 15
#define DAC_DIN  4
#define DAC_BCLK 5
#define DAC_LRC  6

#define HOLD 8
#define HOME_BUTTON       45
#define BACK_BUTTON       47
#define PLAY_PAUSE_BUTTON 46 
#define MENU_BUTTON       48

#define MOTOR_DRIVER 18

#define VOLUME_ROTARY_ENC_A     7
#define VOLUME_ROTARY_ENC_B     21 // we need to relocate this pin it is really 27 but it constantly resets when we use it
#define ROTARY_ENC_BUTTON       16

#endif

#endif