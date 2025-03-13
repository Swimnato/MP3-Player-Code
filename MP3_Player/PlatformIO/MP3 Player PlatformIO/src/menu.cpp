#include "menu.hpp"
#include <Adafruit_GFX.h>
extern Adafruit_ST7789 *tft;
error_t write_string(uint8_t x, uint8_t y, String string, uint16_t color, uint16_t background_color, uint8_t fontSize = 2) {
    tft->setCursor(x, y);
    tft->setTextColor(color, background_color);
    tft->setTextSize(fontSize);
    tft->setTextWrap(false);
    tft->setCursor(x,y);
    tft->print(string);

    return ALL_OK;
}

error_t clear_display() {
    tft->fillScreen(ST77XX_BLACK);
    return ALL_OK;
}

error_t draw_normal_menu_item(uint8_t row, String string) {
    uint8_t text_y = row * FULL_LINE_HEIGHT + LINE_TEXT_SEPERATION;
    
    write_string(0,text_y, ST77XX_BLACK, ST77XX_WHITE);

    return ALL_OK;
}

error_t draw_home_menu(int itemSelected){
    return ALL_OK;
}

error_t draw_settings_menu(){
    return ALL_OK;
}

error_t draw_file_manager(){
    return ALL_OK;
}