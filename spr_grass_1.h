#ifndef SPR_GRASS_H
#define SPR_GRASS_H

#define spr_grass_1_number 1
#define spr_grass_1_width 8
#define spr_grass_1_height 8

// spr_grass_1.png
// 8x8
PROGMEM const unsigned char spr_grass_1[] = {
    // width, height
    8, 8,
    0x20, 0x61, 0xC3, 0xFE, 0xA0, 0xF8, 0x9C, 0x04

};

PROGMEM const unsigned char spr_grass_1_mask[] = {
    // width, height
    8, 8,
    0x20, 0x61, 0xC3, 0xFE, 0xE0, 0xF8, 0x9C, 0x04

};

PROGMEM const unsigned char spr_grass_1_plus_mask[] = {
    // width, height
    8, 8,
    0x20, 0x20, 0x61, 0x61, 0xC3, 0xC3, 0xFE, 0xFE, 0xA0, 0xE0,
    0xF8, 0xF8, 0x9C, 0x9C, 0x04, 0x04,

};

// spr_grass_1_small.png
// 8x8
PROGMEM const unsigned char spr_grass_1_small[] = {
    // width, height
    8, 8,
    0x00, 0x00, 0x48, 0xF0, 0xE0, 0x90, 0x00, 0x00

};

PROGMEM const unsigned char spr_grass_1_small_mask[] = {
    // width, height
    8, 8,
    0x00, 0x00, 0x48, 0xF0, 0xE0, 0x90, 0x00, 0x00

};

PROGMEM const unsigned char spr_grass_1_small_plus_mask[] = {
    // width, height
    8, 8,
    0x00, 0x00, 0x00, 0x00, 0x48, 0x48, 0xF0, 0xF0, 0xE0, 0xE0,
    0x90, 0x90, 0x00, 0x00, 0x00, 0x00,

};

const uint8_t* spr_grass_1_frames[] =
{
    spr_grass_1_plus_mask
};

const uint8_t* spr_grass_1_small_frames[] =
{
    spr_grass_1_small_plus_mask
};
#endif
