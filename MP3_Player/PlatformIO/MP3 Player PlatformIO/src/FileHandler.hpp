#ifndef EE80D13C_87C8_46EB_8F51_1AABB02206F3
#define EE80D13C_87C8_46EB_8F51_1AABB02206F3
#include "ErrorTypes.hpp"
#include <SPI.h>
#include "SdFat.h"
#include "PinConfig.hpp"
#include "sdios.h"
#include "ErrorCodes.hpp"
#include <FatFile.h>

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


error_t mountSD();
error_t unmountSD();
error_t getNextFileWithExtension(byte length, char* extension, byte filenameLength, char* filename);

error_t resetCWD();
error_t enterDirectory(byte length, char* filename);

error_t parseID3Tags(FatFile file);

error_t countFilesInDirectory(FatFile file, uint16_t *numberPointer);



#endif /* EE80D13C_87C8_46EB_8F51_1AABB02206F3 */
