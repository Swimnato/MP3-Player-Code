#include "menu.hpp"
#include <Adafruit_GFX.h>
extern Adafruit_ST7789 *tft;
error_t write_string(uint8_t x, uint8_t y, char* string, uint8_t string_len, uint16_t color, uint16_t background_color) {
    tft->setCursor(x, y);
    tft->setTextColor(color, background_color);
    tft->setTextSize(2);
    tft->setTextWrap(false);
    for (uint8_t i; i++; i<string_len) {
        

    }


}

error_t clear_display() {
    tft->fillScreen(ST77XX_BLACK);
}

error_t draw_normal_menu_item(uint8_t row, char* string) {
    uint8_t text_y = row * FULL_LINE_HEIGHT + LINE_TEXT_SEPERATION;
    

}