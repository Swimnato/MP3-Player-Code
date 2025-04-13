#include "UI.hpp"

UI::UI(FileHandler& FileHandler, InputManager* an_input_manager) : tft(Adafruit_ST7789(SCREEN_CS, SCREEN_DC, -1)), reader(Adafruit_ImageReader(FileHandler.sd)), input_manager(an_input_manager) {
    selected = 0;
    current_settings = CurrentSettings();
}

UI::CurrentSettings::CurrentSettings() {
    font_size = DEFAULT_FONT_SIZE;
    background_color = DEFAULT_MENU_BACKGROUND_COLOR;
}

error_t UI::initialize_screen() {
    tft.init(240, 320); //init or begin?? //need to sd.begin?
    analogWrite(SCREEN_BL, 255);
}

error_t UI::write_string(uint8_t x, uint8_t y, char* string, uint16_t color, uint16_t background_color, uint8_t fontSize) {
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
    write_string(iconWithLabel.x, iconWithLabel.text_y, iconWithLabel.label, MENU_TEXT_COLOR, current_settings.background_color, current_settings.font_size);
    return ALL_OK;
}

error_t UI::draw_home_menu() {
    tft.fillScreen(current_settings.background_color);
    //Adafruit_ImageReader reader(sd);
    for(icon_with_label each_icon_with_label : MENU_ICONS) {
        draw_icon_with_label(each_icon_with_label);
    }
    draw_item_selection_box();
    return ALL_OK;
}

void UI::draw_item_selection_box() { //for the main menu
    //draws a selection box around the given item
    icon_with_label& icon_to_select = MENU_ICONS[selected];//no bounds checking here
    tft.drawRect(icon_to_select.x - MENU_SELECTION_OFFSET,
        icon_to_select.y - MENU_SELECTION_OFFSET,
        ICON_WIDTH + 2 * MENU_SELECTION_OFFSET,
        ICON_HEIGHT + 2 * MENU_SELECTION_OFFSET + current_settings.font_size, //add font size to account for the height of the text
        MENU_SELECTION_COLOR);
}
    
error_t UI::draw_music_player() {
    return ALL_OK;
}
    
error_t UI::draw_file_manager() {
    return ALL_OK;
}

error_t UI::draw_settings_menu() {
    return ALL_OK;
}

void UI::ready_new_program() {
    input_manager -> getTurnAmount(); //keep scrolling from the last menu from carrying over to the new one
    selected = 0; //always start on the first icon; plus this lets us reuse selected between settings and home menus
}

error_t UI::open_home_menu() {
    ready_new_program();
    draw_home_menu();
}

error_t UI::open_music_player() {
    ready_new_program();
    draw_music_player(); //will get redrawn by music_update if something changes, but someone's got to draw it the first time
    return ALL_OK;
}
    
error_t UI::open_file_manager() {
    ready_new_program();
    draw_file_manager();
    return ALL_OK;
}

error_t UI::open_settings_menu() {
    ready_new_program();
    draw_settings_menu();
    return ALL_OK;
}

void UI::home_menu_update() {
    if (input_manager -> isPlayPausePressed()) {
        switch (selected) {
            case 0: //music
                current_menu = MUSIC;
                open_music_player(); //it'll be drawn again when update() is called if something changed, but something has to draw it the first time
                break;
            case 1: //files
                current_menu = FILE_MENU;
                open_file_manager();
                break;
            case 2: //settings
                current_menu = SETTINGS;
                open_settings_menu();
                break;
            case 3: //DOOM
                //TODO: run doom
                break;
        }
        return; //no further updates are relevant
    }
    short turn_amount = input_manager -> getTurnAmount(); //how much have we scrolled?
    if (turn_amount) {
        selected += turn_amount;
        selected %= 4; //loop around
        draw_home_menu(); //only need to redraw if the selected item changed
    }
}

void UI::music_player_update() {
    return;
}

void UI::file_manager_update() {
    return;
}

void UI::settings_menu_update() { //very similar to home_menu_update
    if (input_manager -> isPlayPausePressed()) {
        switch (selected) {
            case 0://TODO: Add the rest
            break;
        }
    }
    short turn_amount = input_manager -> getTurnAmount(); //how much have we scrolled?
    if (turn_amount) {
        selected += turn_amount;
        keep_in_bounds(selected); //don't run off the beginning or end of the list
        draw_settings_menu(); //only need to redraw if the selected item changed
    }
}

void UI::update() { //gets called every frame when in the ui
    switch (current_menu) {
        case MAIN_MENU:
            home_menu_update();
            break;
        case SETTINGS:
            settings_menu_update();
            break;
        case FILE_MENU:
            file_manager_update();
            break;
        case MUSIC:
            music_player_update();
            break;
    }
}