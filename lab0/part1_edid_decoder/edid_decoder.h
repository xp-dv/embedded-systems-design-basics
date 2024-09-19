//* Lab 0 - C Programming Refresher | Part 1 - EDID Decoder and writer

// TASK #1: Parse the EDID and display the following
/**
 * Video Interface
 * Audio Format Code
 * Supported Maximum Channels
 * Supported Sample Frequencies
 * Supported Bit Depth
 */

// TASK #2: Write the following data to the EDID block
/**
 * Video Interface = DisplayPort
 * Audio Format Code (Unchanged)
 * Supported Maximum Channels = 2
 * Supported Sample Frequencies = 48 kHz (only)
 * Supported Bit Depth = 24-bit (only)
 */

/**
 * ? EDID Information:
 * The first 128 bytes (bytes 0-127) make up the EDID Base Block
 * The last 128 bytes (bytes 128-255) make up the CTA Extension Block based on the CTA 861 std
 * Bytes 0-7 are always the fixed header pattern "0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00"
 * Video Interface Type (Digital or Analog) at byte 20, bit 7
 * Video Interface Standard (HDMI, DVI, etc) at Byte 20, bits 0-4
 * The last byte, byte 127, is always a checksum. Checksums are calculated when the EDID is generated
 * 
 * Byte 128 of the EDID (byte 0 of the CTA Extension Block) is the Extension Tag. Always 0x02 for CTA Extension Blocks
 * Byte 1 of the CTA Extension Block (Byte 129 of the EDID) is the CTA Extension Block revision number
 * Byte 2 of the CTA Extension Block (Byte 130 of the EDID) is the byte # within the CTA Extension Block at which the Detailed Timing Descriptor (DTD) information begins
 * The last byte of the CTA Extension Block, byte 255 of the EDID, is always a checksum. Checksums are calculated when the EDID is generated
 * 
 * Bytes 4 to (value of byte 2 minus 1) of the CTA Extension Block make up the Data Block Collection (DBC)
 * If byte 2 = 0x00, the DBC makes up the rest of the CTA Extension Block. If byte 2 = 0x04, the rest of the CTA Extension Block consists of DTDs
 * Byte 4 of the DBC is the first byte (byte 0) of the first Data Block (DB), and the first byte of every Data Block afterwards (until the byte given in DBC byte 2) will be a Data Block header
 * Within the DBC, byte 0 of every Data Block is the Data Block header. Bits 7-5 indicate Data Block type. If Data Block type = 0b111, use the extended Data Block type indicator in byte 1. Bits 4-0 indicate # of remaining bytes in this block after byte 0
 * 
 * A Data Block with a Block Type Tag of 0b001 (bits 7-5 of the Data Block header at byte 0) is an Audio Data Block (ADB)
 * Audio Data Blocks consist of one or more 3-byte Short Audio Descriptors (SADs) after the Data Block header at byte 0
 * SAD byte 0, bit 7 is reserved 0, bits 6-3 indicate audio format, bits 2-0 indicate the maximum supported number of channels
 * SAD byte 1, bit 7 is reserved 0, bits 6-0 indicate the supported sampling freqencies with each bit representing a single frequency in kHz
 * SAD byte 2 is format dependent:
  * For audio format code 1 (LPCM), bits 7-3 are reserved, and bits 2-0 indicate the supported bit-depths with each bit representing a single bit-depth.
  * For audio format codes 2-8, byte 3 represents bitrate in kbps divided by 8 and vice-versa (i.e. byte 3 times 8 will give the bitrate in kbps)
  * For audio format codes 9-14, its even more specific to the format and is too complex to cover here
  * For audio format code 15 (Extended), bits 7-3 represent the extended audio format code (most of the extended codes refer to different versions of MPEG-4). Bits 2-0 are format dependent
 */

#pragma once

//* Standard Headers
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
