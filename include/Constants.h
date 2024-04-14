#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <cstdint>

enum ExitCodes {
    kSuccess = 0,
    // Parsing
    kFileIOError = 1,
    kFileParseError = 2,
    kSettingNotExists = 3,
    kConfigValueNotFound = 4,
    // Work with files
    kFileNotOpen = 5,

    kExitCodesMax // Should be last at enum
};

#endif // CONSTANTS_H_