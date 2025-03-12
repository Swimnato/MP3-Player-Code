
#include "FileHandler.hpp"



error_t mountSD() {
    if (!sd.begin(SD_CONFIG)) {
        sd.initErrorHalt(&Serial);
    }
    // Open root directory
    if (!dir.open("/")) {
        error("dir.open failed");   
    }   
}