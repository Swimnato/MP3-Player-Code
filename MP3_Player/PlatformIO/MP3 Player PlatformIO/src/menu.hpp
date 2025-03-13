#ifndef C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#define C2D5D070_FF5F_4389_B03A_63C31BBB4A24
#include "ErrorTypes.hpp"
#include "main.hpp"
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "ErrorCodes.hpp"

#define LINE_TEXT_SEPERATION 2
#define TEXT_HEIGHT 16
#define LINE_WIDTH 1
#define FULL_LINE_HEIGHT LINE_TEXT_SEPERATION + 2*TEXT_HEIGHT + LINE_WIDTH

#define TEXT_X_START 4

extern Adafruit_ST7789 *tft;

error_t clear_display();

error_t draw_selected_menu_item(uint8_t row, char* string, uint8_t string_len, uint8_t scroll_string_location);
error_t draw_normal_menu_item(uint8_t row, char* string, uint8_t string_len);
error_t write_string(uint8_t x, uint8_t y, char* string, uint8_t string_len);

#endif /* C2D5D070_FF5F_4389_B03A_63C31BBB4A24 */
