#include "FileHandler.hpp"

SdFs sd;
FsFile file;
FsFile root;

char cinBuf[40];
ArduinoInStream cin(Serial, cinBuf, sizeof(cinBuf));

error_t mountSD() {
    if (!sd.begin(SD_CONFIG)) {
        sd.initErrorHalt(&Serial);
    }
    // Open root directory
    if (!dir.open("/")) {
        error("dir.open failed");   
    }   
}