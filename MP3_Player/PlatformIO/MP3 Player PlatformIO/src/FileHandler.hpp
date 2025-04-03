#ifndef EE80D13C_87C8_46EB_8F51_1AABB02206F3
#define EE80D13C_87C8_46EB_8F51_1AABB02206F3
#include "ErrorTypes.hpp"
#include <SPI.h>
#include "SdFat.h"
#include "PinConfig.hpp"
#include "sdios.h"
#include "ErrorCodes.hpp"
#include <Arduino.h>

#define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.

#define SPI_SPEED SD_SCK_MHZ(4)

// Try to select the best SD card configuration.
#if defined(HAS_TEENSY_SDIO)
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif defined(RP_CLK_GPIO) && defined(RP_CMD_GPIO) && defined(RP_DAT0_GPIO)
// See the Rp2040SdioSetup example for RP2040/RP2350 boards.
#define SD_CONFIG SdioConfig(RP_CLK_GPIO, RP_CMD_GPIO, RP_DAT0_GPIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_SPEED)
#else  // HAS_TEENSY_SDIO
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_SPEED)
#endif  // HAS_TEENSY_SDIO

typedef struct ID3Tags {
    char artist[20];
    char album[20];
    char title[20];
    uint8_t track_number;
    uint8_t disc_number;
};

class FileHandler {   
private:

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
    ArduinoInStream cin;

    public:
        error_t mountSD();
    
        error_t unmountSD();
    
        error_t getNextFileWithExtension(byte length, char* extension, byte filenameLength, char* filename);

        error_t resetCWD();
        error_t enterDirectory(byte length, char* filename);
        
        error_t parseID3Tags(FatFile file, ID3Tags *tags);
        
        error_t countFilesInDirectory(FatFile file, uint16_t *numberPointer);        
    };

//THESE LINES BREAK THE COMPILER!!!!!!!!!

// error_t mountSD();
// error_t unmountSD();
// error_t getNextFileWithExtension(byte length, char* extension, byte filenameLength, char* filename);

// error_t resetCWD();
// error_t enterDirectory(byte length, char* filename);

// error_t parseID3Tags(FatFile file);

// error_t countFilesInDirectory(FatFile file, uint16_t *numberPointer);

#endif /* EE80D13C_87C8_46EB_8F51_1AABB02206F3 */
