#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <vector>
#include <datatypes.h>
using namespace std;


enum commandNames
{
    BRIGHTNESS_SETTING = 0,
    BRIGHTNESS_SETTING_STATUS,
    TOGGLE_2D_3D_SELECT_2D,
    TOGGLE_2D_3D_SELECT_3D,
    TOGGLE_2D_3D_SELECT_STATUS,
    IMAGE_INTENSITY_STATUS,
    IMAGE_INTENSITY,
    IMAGE_SHARPNESS_STATUS,
    IMAGE_SHARPNESS

};

vector<vector<UChar>> commandCodes{
    // Commands To Communicate With Eizo Monitor
    VChar{0x30, 0x03, 0x02, 0x00, 0x04, 0, 0x00},  // BRIGHTNESS_SETTING
    VChar{0x31, 0x03, 0x01, 0x00, 0x04, 0x00},     // BRIGHTNESS_SETTING_STATUS
    VChar{0xC0, 0x01, 0x01, 0x00, 0x02, 0x00},     // TOGGLE_2D_3D_SELECT_2D
    VChar{0xC0, 0x01, 0x01, 0x00, 0x01, 0x00},     // TOGGLE_2D_3D_SELECT_3D
    VChar{0xC1, 0x01, 0x00, 0x00, 0x00},           // TOGGLE_2D_3D_SELECT_STATUS
    VChar{0x31, 0x04, 0x01, 0x00, 0x04, 0x00},     // IMAGE_INTENSITY_STATUS
    VChar{0x30, 0x04, 0x02, 0x00, 0x04, 50, 0x00}, // IMAGE_INTENSITY
    VChar{0x31, 0x05, 0x01, 0x00, 0x04, 0x00},     // IMAGE_SHARPNESS_STATUS
    VChar{0x30, 0x05, 0x02, 0x00, 0x04, 0, 0x00}   // IMAGE_SHARPNESS
};

vector<pair<UChar *, int>> commandCodesPtr;

#endif
