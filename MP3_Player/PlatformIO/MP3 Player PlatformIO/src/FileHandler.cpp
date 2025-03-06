#include "FileHandler.hpp"

SdFs sd;
FsFile file;
FsFile root;

char cinBuf[40];
ArduinoInStream cin(Serial, cinBuf, sizeof(cinBuf));

error_t mountSD() {
    return 0;
}