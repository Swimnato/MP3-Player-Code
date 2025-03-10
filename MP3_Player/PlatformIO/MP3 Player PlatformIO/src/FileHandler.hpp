#ifndef EE80D13C_87C8_46EB_8F51_1AABB02206F3
#define EE80D13C_87C8_46EB_8F51_1AABB02206F3
#include "ErrorTypes.hpp"
#include <SPI.h>
#include "SdFat.h"
#include "PinConfig.hpp"
#include "sdios.h"


#define SPI_SPEED SD_SCK_MHZ(4)


error_t mountSD();
error_t unmountSD();
error_t getNextFileWithExtension(uint8_t length, char* extension, uint8_t filenameLength, char* filename);

error_t resetCWD();
error_t enterDirectory(uint8_t length, char* filename);


#endif /* EE80D13C_87C8_46EB_8F51_1AABB02206F3 */
