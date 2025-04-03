#define MENU_BACKGROUND_COLOR ST77XX_BLACK
#define MENU_TEXT_COLOR ST77XX_WHITE

class icon_with_label {
    public:
    char[64] icon_filename;
    char[16] label;
    uint8_t text_size;
    uint8_t x;
    uint8_t y;
    int32_t text_y;

    icon_with_label(uint8_t* an_icon, char* a_label, uint8_t label_size, uint8_t xpos, uint8_t ypos) { //positions are of top left corner
        icon_filename = an_icon;
        label = a_label;
        text_size = label_size;
        x = xpos;
        y = ypos;
        int32_t width = 0;
        int32_t height = 0;
        reader.bmpDimensions(icon_filename, &width, &height);
        text_y = y + height;
    }

    error_t draw_icon_with_label(Adafruit_ST7789& screen, Adafruit_ImageReader& reader) {
        reader.drawBMP(icon_filename, screen, x, y);
        write_string(x, text_y, label, text_size, MENU_TEXT_COLOR, MENU_BACKGROUND_COLOR);
        return ALL_OK;
    }
};

#define MENU_ICONS {\
    icon_with_label("music.bmp","Music",5,10,10),\
    icon_with_label("files.bmp","Files",5,10,170),\
    icon_with_label("settings.bmp","Settings",8,130,10),\
    icon_with_label("doom.bmp","DOOM",4,130,170)\
};