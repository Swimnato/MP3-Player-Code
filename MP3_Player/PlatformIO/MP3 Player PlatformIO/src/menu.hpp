#ifndef C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#define C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#include "ErrorTypes.hpp"
#include "main.hpp"
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "ErrorCodes.hpp"
#include "FileHandler.hpp"
#include <Adafruit_Imagereader.h>
#include "menu_icons.h"
#include "FileHandler.hpp"

class Menu {
    private:
    Adafruit_ST7789 tft;
    Adafruit_ImageReader reader;
    public:

    Menu(FileHandler FileHandler);
    error_t initialize_screen();
    error_t write_string(uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize = 2);
    error_t draw_home_menu(int itemSelected);
    error_t draw_settings_menu();
    error_t draw_file_manager();
    void drawBMP(char* filename,int x, int y);
    error_t draw_icon_with_label(icon_with_label& IconWithLabel);
    void draw_item_selection_box(int item);
};

#endif /* C2D5D070_FF5F_4389_B03A_63C31BBB4A24 */
