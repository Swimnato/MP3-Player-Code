#include <FileHandler.hpp>

error_t FileHandler::mountSD() {
    cin = ArduinoInStream(Serial, cinBuf, sizeof(cinBuf));
    if (!sd.begin(SD_CONFIG)) {
        sd.initErrorHalt(&Serial);
    }
    // Open root directory
    if (!dir.open("/")) {
        Serial.println("dir.open failed");   
        return SD_OPEN_ERROR;
    }
    return ALL_OK;
}

error_t FileHandler::unmountSD() {
    sd.end();
    return ALL_OK;
}



error_t FileHandler::parseID3Tags(FatFile file, ID3Tags *tags){
    return ALL_OK;
}