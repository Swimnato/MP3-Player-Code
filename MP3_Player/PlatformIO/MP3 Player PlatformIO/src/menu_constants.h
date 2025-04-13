#define MENU_BACKGROUND_COLOR ST77XX_BLACK
#define MENU_TEXT_COLOR ST77XX_WHITE
#define MENU_SELECTION_COLOR ST77XX_WHITE
#define MENU_SELECTION_OFFSET 5
#define DEFAULT_FONT_SIZE 5
#define ICON_HEIGHT 24
#define ICON_WIDTH 24
#include "UI.hpp"

class icon_with_label { //used in main menu
    public:
    char icon_filename[64];
    char label[16];
    uint8_t text_size;
    uint8_t x;
    uint8_t y;
    int32_t text_y;

    icon_with_label(char* icon, char* label, uint8_t label_size, uint8_t xpos, uint8_t ypos) { //positions are of top left corner
        strcpy(icon_filename, icon);
        strcpy(this->label, label);
        text_size = label_size;
        x = xpos;
        y = ypos;
        text_y = y + ICON_HEIGHT;
    }
};

icon_with_label MENU_ICONS[4] = {
    icon_with_label("music.bmp","Music",5,10,10),
    icon_with_label("files.bmp","Files",5,10,170),
    icon_with_label("settings.bmp","Settings",8,130,10),
    icon_with_label("doom.bmp","DOOM",4,130,170)
};