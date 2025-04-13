#ifndef C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#define C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#include "ErrorTypes.hpp"
#include "main.hpp"
#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "ErrorCodes.hpp"
#include "FileHandler.hpp"
#include <Adafruit_Imagereader.h>
#include "menu_constants.h"
#include "FileHandler.hpp"
#include "InputManager.hpp"

enum CurrentMenu:uint8_t {
    SETTINGS,
    MAIN_MENU,
    FILE_MENU,
    MUSIC
};

class UI {
    private:
    Adafruit_ST7789 tft;
    Adafruit_ImageReader reader;
    InputManager* input_manager;
    int selected; //0-3, which icon is selected, goes in order of music, files, settings, DOOM
    public:
    CurrentMenu current_menu = MAIN_MENU;

    UI(FileHandler& FileHandler, InputManager& an_input_manager);
    error_t initialize_screen();
    error_t write_string(uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize);
    error_t draw_home_menu();
    error_t draw_music_player();
    error_t draw_file_manager();
    error_t draw_settings_menu();
    void ready_new_program();
    error_t open_music_player();
    error_t open_file_manager();
    error_t open_settings_menu();
    void drawBMP(char* filename,int x, int y);
    error_t draw_icon_with_label(icon_with_label& IconWithLabel);
    void draw_item_selection_box();
    void home_menu_update();
    void music_player_update();
    void file_manager_update();
    void settings_menu_update();
    void update();
};

#endif /* C2D5D070_FF5F_4389_B03A_63C31BBB4A24 */
