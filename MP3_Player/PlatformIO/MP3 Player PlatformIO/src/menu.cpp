#include "menu.hpp"

Menu::Menu(FileHandler FileHandler) : tft(Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1)), reader(Adafruit_ImageReader(FileHandler.sd)){

}

error_t Menu::initialize_screen() {
    tft.init(240, 320); //init or begin?? //need to sd.begin?
    analogWrite(SCREEN_BL, 255);
}

error_t Menu::write_string(uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize = 2) {
    tft.setCursor(x, y);
    tft.setTextColor(color, background_color);
    tft.setTextSize(fontSize);
    tft.setTextWrap(false);
    tft.setCursor(x,y);
    tft.print(string);

    return ALL_OK;
}

void Menu::drawBMP(char* filename,int x, int y) {
    reader.drawBMP(filename, tft, x, y);
}

error_t Menu::draw_icon_with_label(icon_with_label& iconWithLabel) {
    drawBMP(iconWithLabel.icon_filename, iconWithLabel.x, iconWithLabel.y);
    write_string(iconWithLabel.x, iconWithLabel.text_y, iconWithLabel.label, iconWithLabel.text_size, MENU_TEXT_COLOR, MENU_BACKGROUND_COLOR);
    return ALL_OK;
}

error_t Menu::draw_home_menu(int itemSelected){
    
    tft.fillScreen(MENU_BACKGROUND_COLOR);
    //Adafruit_ImageReader reader(sd);
    for(icon_with_label each_icon_with_label : MENU_ICONS) {
        draw_icon_with_label(each_icon_with_label);
    }
    draw_item_selection_box(itemSelected);
    return ALL_OK;
}
    
error_t Menu::draw_settings_menu(){
    return ALL_OK;
}
    
error_t Menu::draw_file_manager(){
    return ALL_OK;
}