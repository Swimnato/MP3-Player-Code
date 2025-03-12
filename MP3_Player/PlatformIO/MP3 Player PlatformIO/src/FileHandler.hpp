#ifndef EE80D13C_87C8_46EB_8F51_1AABB02206F3
#define EE80D13C_87C8_46EB_8F51_1AABB02206F3
<<<<<<< HEAD
#include "ErrorTypes.h"
#include <SPI.h>
#include "SdFat.h"
#include "PinConfig.h"
#include "sdios.h"

#define DISABLE_FS_H_WARNING  // Disable warning for type File not defined.

SdFs sd;
FsFile file;
FsFile root;
#define SPI_SPEED SD_SCK_MHZ(4)

#if SD_FAT_TYPE == 0
SdFat sd;
File dir;
File file;
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

// Try to select the best SD card configuration.
#if defined(HAS_TEENSY_SDIO)
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif defined(RP_CLK_GPIO) && defined(RP_CMD_GPIO) && defined(RP_DAT0_GPIO)
// See the Rp2040SdioSetup example for RP2040/RP2350 boards.
#define SD_CONFIG SdioConfig(RP_CLK_GPIO, RP_CMD_GPIO, RP_DAT0_GPIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else  // HAS_TEENSY_SDIO
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif  // HAS_TEENSY_SDIO


char cinBuf[40];
ArduinoInStream cin(Serial, cinBuf, sizeof(cinBuf));


error_t mountSD();
error_t unmountSD();
error_t getNextFileWithExtension(uint8_t length, char* extension, uint8_t filenameLength, char* filename);

error_t resetCWD();
error_t enterDirectory(uint8_t length, char* filename);


#endif /* EE80D13C_87C8_46EB_8F51_1AABB02206F3 */
