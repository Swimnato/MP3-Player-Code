#include "menu.hpp"
#include "FileHandler.hpp"
#include <Adafruit_Imagereader.h>
#include "menu_icons.h"
error_t write_string(Adafruit_ST7789* screen, uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize = 2) {
    screen->setCursor(x, y);
    screen->setTextColor(color, background_color);
    screen->setTextSize(fontSize);
    screen->setTextWrap(false);
    screen->setCursor(x,y);
    screen->print(string);

    return ALL_OK;
}

error_t draw_home_menu(int itemSelected, Adafruit_ST7789& screen, Adafruit_ImageReader& reader){
    
    screen->fillScreen(MENU_BACKGROUND_COLOR);
    //Adafruit_ImageReader reader(sd);
    for(icon_with_label each_icon_with_label : MENU_ICONS) {
        each_icon_with_label.draw_icon_with_label(screen, reader);
    }
    draw_item_selection_box(itemSelected);
    return ALL_OK;
}

error_t draw_settings_menu(){
    return ALL_OK;
}

error_t draw_file_manager(){
    return ALL_OK;
}