#include <FileHandler.hpp>
#include <FatFile.h>

#if SD_FAT_TYPE == 0
SdFat sd;
FsFile dir;
FsFile file;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 dir;
File32 file;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile dir;
ExFile file;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile dir;
FsFile file;
#else  // SD_FAT_TYPE
#error invalid SD_FAT_TYPE
#endif  // SD_FAT_TYPE

char cinBuf[40];
ArduinoInStream cin(Serial, cinBuf, sizeof(cinBuf));

typedef struct ID3Tags {
    char[20] artist;
    char[20] album;
    char[20] title;
    uint8_t track_number;
    uint8_t disc_number;
}

error_t mountSD() {
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

error_t unmountSD() {
    sd.end();
}



error_t parseID3Tags(FatFile file, ID3Tags *tags);