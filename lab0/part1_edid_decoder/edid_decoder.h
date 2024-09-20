//* Lab 0 - C Programming Refresher | Part 1 - EDID Decoder and writer

#pragma once

//* Headers
#include <stdint.h>

//* Enumerations
typedef enum {
  UNDEFINED,
  DVI,
  HDMIA,
  HDMIB,
  MDDI,
  DISPLAYPORT,
  ANALOG = 0xFF
} video_interface_t;

typedef enum {
  DB_TYPE_AUDIO = 1,
  DB_TYPE_VIDEO,
  DB_TYPE_VSDB,
  DB_TYPE_SADB,
  DB_TYPE_VESA_DTC,
  DB_TYPE_VFDB,
  DB_TYPE_EXTENDED
} data_block_type_t;

typedef enum {
  SAD_FORMAT_LPCM = 1,
  SAD_FORMAT_AC_3,
  SAD_FORMAT_MPEG_1,
  SAD_FORMAT_MP3,
  SAD_FORMAT_MPEG_2,
  SAD_FORMAT_AAC_LC,
  SAD_FORMAT_DTS,
  SAD_FORMAT_ATRAC,
  SAD_FORMAT_DSD,
  SAD_FORMAT_DD_PLUS,
  SAD_FORMAT_DTS_HD,
  SAD_FORMAT_DOLBY_MAT,
  SAD_FORMAT_DST_AUDIO,
  SAD_FORMAT_MS_WMA_PRO,
  SAD_FORMAT_EXTENDED
} sad_format_t;

//* Global Macros
#define BIT_7_MASK 0x80U
#define BIT_6_MASK 0x40U
#define BIT_5_MASK 0x20U
#define BIT_4_MASK 0x10U
#define BIT_3_MASK 0x08U
#define BIT_2_MASK 0x04U
#define BIT_1_MASK 0x02U
#define BIT_0_MASK 0x01U

// TODO: The following macros could be made into constants within their respective functions, like the other constants, but were made global for quick implementation of the write_edid() function
#define VIDEO_INTERFACE_BYTE 20U //? "U" is the unsigned integer literal
#define VIDEO_INTERFACE_MASK 0x0FU // Bits 3-0
#define SAD_CHANNEL_MASK 0x07U // Bits 2-0

//* Function Prototypes
// Use pointers when passing arrays to functions because passing an array to a function will always decay it to a pointer of its first element anyway
int decode_edid(const uint8_t* edid);
int print_video_interface(const uint8_t* edid);
int parse_extension_block(const uint8_t* extension_block);
int parse_data_block_collection(const uint8_t* dbc, int dbc_size);
int parse_data_block_audio(const uint8_t* data, int block_size);
int write_edid(uint8_t* edid, const uint8_t byte_value, const uint8_t byte_i);
uint8_t set_bits(const uint8_t mask, uint8_t old_value, uint8_t new_value);
