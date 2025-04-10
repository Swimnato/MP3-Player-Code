#include "UI.hpp"

UI::UI(FileHandler& FileHandler, InputManager& an_input_manager) : tft(Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1)), reader(Adafruit_ImageReader(FileHandler.sd)), input_manager(&an_input_manager) {
    selected = 0;
}

error_t UI::initialize_screen() {
    tft.init(240, 320); //init or begin?? //need to sd.begin?
    analogWrite(SCREEN_BL, 255);
}

error_t UI::write_string(uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize = DEFAULT_FONT_SIZE) {
    tft.setCursor(x, y);
    tft.setTextColor(color, background_color);
    tft.setTextSize(fontSize);
    tft.setTextWrap(false);
    tft.setCursor(x,y);
    tft.print(string);

    return ALL_OK;
}

void UI::drawBMP(char* filename,int x, int y) {
    reader.drawBMP(filename, tft, x, y);
}

error_t UI::draw_icon_with_label(icon_with_label& iconWithLabel) {
    drawBMP(iconWithLabel.icon_filename, iconWithLabel.x, iconWithLabel.y);
    write_string(iconWithLabel.x, iconWithLabel.text_y, iconWithLabel.label, iconWithLabel.text_size, MENU_TEXT_COLOR, MENU_BACKGROUND_COLOR);
    return ALL_OK;
}

error_t UI::draw_home_menu() {
    tft.fillScreen(MENU_BACKGROUND_COLOR);
    //Adafruit_ImageReader reader(sd);
    for(icon_with_label each_icon_with_label : MENU_ICONS) {
        draw_icon_with_label(each_icon_with_label);
    }
    draw_item_selection_box();
    return ALL_OK;
}

void UI::draw_item_selection_box() {
    //draws a selection box around the given item
    //item is an int from 0-3
    icon_with_label& icon_to_select = MENU_ICONS[selected];//no bounds checking here
    tft.drawRect(icon_to_select.x - MENU_SELECTION_OFFSET,
        icon_to_select.y - MENU_SELECTION_OFFSET,
        ICON_WIDTH + 2 * MENU_SELECTION_OFFSET,
        ICON_HEIGHT + 2 * MENU_SELECTION_OFFSET + DEFAULT_FONT_SIZE, //add font size to account for the height of the text
        MENU_SELECTION_COLOR);
}
    
error_t UI::draw_settings_menu(){
    return ALL_OK;
}
    
error_t UI::draw_file_manager(){
    return ALL_OK;
}

void UI::update() { //gets called every frame when in the ui
    //get offset
    //get click
    if (click) {
        //how do we handle global state?
    }
    if (offset) {
        item += offset;
        item %= 4;
        draw_home_menu();
    }
}