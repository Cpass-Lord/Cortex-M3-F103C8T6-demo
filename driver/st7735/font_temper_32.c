#include <stdint.h>
#include "stfonts.h"

static const uint8_t font_temper_16x32_data[][65] =
    {
        {'0', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0F, 0xF8, 0x1E, 0x3C, 0x3C, 0x3C, 0x3C, 0x1E, 0x38, 0x1E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x78, 0x0E, 0x38, 0x1E, 0x3C, 0x1E, 0x3C, 0x1C, 0x1E, 0x3C, 0x1F, 0xF8, 0x07, 0xF0, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'1', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x01, 0xE0, 0x03, 0xE0, 0x07, 0xE0, 0x1F, 0xE0, 0x1D, 0xE0, 0x19, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'2', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1F, 0xFC, 0x3E, 0x3C, 0x3C, 0x1E, 0x78, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x78, 0x00, 0xF0, 0x00, 0xE0, 0x01, 0xE0, 0x03, 0xC0, 0x07, 0x80, 0x0F, 0x00, 0x1E, 0x00, 0x3E, 0x00, 0x3F, 0xFE, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'3', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0F, 0xFC, 0x1E, 0x3C, 0x3C, 0x1E, 0x38, 0x1E, 0x18, 0x1E, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x7C, 0x03, 0xF0, 0x03, 0xF8, 0x00, 0x7C, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x1E, 0x18, 0x0E, 0x78, 0x1E, 0x3C, 0x1E, 0x3E, 0x3C, 0x1F, 0xFC, 0x0F, 0xF0, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'4', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x78, 0x00, 0x78, 0x00, 0xF8, 0x01, 0xF8, 0x01, 0xF8, 0x03, 0xF8, 0x07, 0xB8, 0x0F, 0x38, 0x0E, 0x38, 0x1E, 0x38, 0x3C, 0x38, 0x38, 0x38, 0x78, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'5', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x1F, 0xFC, 0x1C, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x38, 0x00, 0x3F, 0xE0, 0x3F, 0xF8, 0x7C, 0x7C, 0x78, 0x3C, 0x00, 0x1E, 0x00, 0x1E, 0x00, 0x0E, 0x00, 0x0E, 0x30, 0x1E, 0x70, 0x1E, 0x78, 0x1E, 0x78, 0x7C, 0x3F, 0xF8, 0x1F, 0xF0, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'6', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x01, 0xE0, 0x03, 0xC0, 0x03, 0xC0, 0x07, 0x80, 0x0F, 0x00, 0x0F, 0x00, 0x1F, 0xF8, 0x1F, 0xFC, 0x3E, 0x1E, 0x3C, 0x0F, 0x78, 0x0F, 0x78, 0x0F, 0x78, 0x0F, 0x78, 0x0F, 0x78, 0x0F, 0x3C, 0x0F, 0x3E, 0x1E, 0x1F, 0xFC, 0x0F, 0xF8, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'7', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x7F, 0xFF, 0x00, 0x0F, 0x00, 0x1E, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x38, 0x00, 0x78, 0x00, 0x70, 0x00, 0xF0, 0x00, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x01, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'8', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1F, 0xF8, 0x3C, 0x3C, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1E, 0x38, 0x1E, 0x3C, 0x3C, 0x3E, 0x7C, 0x0F, 0xF0, 0x1F, 0xF8, 0x3E, 0x7C, 0x7C, 0x1E, 0x78, 0x1E, 0x70, 0x0E, 0x70, 0x0E, 0x78, 0x0E, 0x78, 0x1E, 0x7C, 0x3E, 0x3F, 0xFC, 0x1F, 0xF8, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'9', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x1F, 0xF8, 0x3E, 0x7C, 0x78, 0x3E, 0x78, 0x1E, 0x70, 0x1E, 0x70, 0x1E, 0x70, 0x1E, 0x70, 0x1E, 0x78, 0x3C, 0x7C, 0x7C, 0x3F, 0xFC, 0x1F, 0xF8, 0x00, 0xF0, 0x00, 0xF0, 0x01, 0xE0, 0x01, 0xE0, 0x03, 0xC0, 0x03, 0xC0, 0x07, 0x80, 0x07, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {' ', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {'C', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x0F, 0xFC, 0x1F, 0x3E, 0x1E, 0x1E, 0x3C, 0x0E, 0x3C, 0x0F, 0x3C, 0x0F, 0x78, 0x0F, 0x78, 0x00, 0x78, 0x00, 0x78, 0x00, 0x78, 0x00, 0x78, 0x00, 0x78, 0x0F, 0x78, 0x0F, 0x3C, 0x0F, 0x3C, 0x0E, 0x3C, 0x1E, 0x1E, 0x3E, 0x0F, 0xFC, 0x07, 0xF8, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

st_fonts_t font_temper_16x32 =
    {
        .width = 16,
        .height = 32,
        .data = (const uint8_t *)font_temper_16x32_data,
        .count = sizeof(font_temper_16x32_data) / sizeof(font_temper_16x32_data[0]),
};
