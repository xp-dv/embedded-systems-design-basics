//* Lab 0 - C Programming Refresher | Part 1 - EDID Decoder and Writer

//* Headers
#include "edid_decoder.h"

#include <stdio.h>
#include <stdint.h>

//* Functions
int decode_edid(const uint8_t* edid) {
  const uint8_t EXTENSION_BLOCK_START_BYTE = 128U; //? "U" is the unsigned integer literal
  const uint8_t EXTENSION_BLOCK_TAG = 0x02U;

  // Base Block
  printf("----Base Block----\n");
  print_video_interface(edid);

  // CTA Extension Block
  printf("----Extension Block----\n");
  if (edid[EXTENSION_BLOCK_START_BYTE] == EXTENSION_BLOCK_TAG) {
    parse_extension_block(&edid[EXTENSION_BLOCK_START_BYTE]); // Passing the address of the start byte still passes the actual array, but starting at EXTENSION_BLOCK_START_BYTE
  }
  else {
    printf("No CEA Extension Block Detected.\n");
  }

  printf("\n");
  return 0;
}

int print_video_interface(const uint8_t* edid) {
  const uint8_t VIDEO_INTERFACE_TYPE_MASK = 0x80U; // Bit 7
  // Get video interface identification number
  video_interface_t video_interface = (edid[VIDEO_INTERFACE_BYTE] & VIDEO_INTERFACE_TYPE_MASK) ? edid[VIDEO_INTERFACE_BYTE] & VIDEO_INTERFACE_MASK : ANALOG;

  // Parse and print corresponding interface type according to EDID specification
  printf("Video Interface: ");
  switch(video_interface) {
    case UNDEFINED: printf("Undefined\n"); break;
    case DVI: printf("DVI\n"); break;
    case HDMIA: printf("HDMIa\n"); break;
    case HDMIB: printf("HDMIb\n"); break;
    case MDDI: printf("MDDI\n"); break;
    case DISPLAYPORT: printf("DisplayPort\n"); break;
    case ANALOG: printf("Analog\n"); break;
    default: printf("Unexpected Data\n"); break;
  }

  return 0;
}

int parse_extension_block(const uint8_t* extension_block) {
  const uint8_t DTD_START_BYTE_INDICATOR = 2U; // The byte at index 2 of the extension block = the index of the first byte of the DTD
  const uint8_t DBC_START_BYTE = 4U;

  // Data Block Collection
  int dbc_size = extension_block[DTD_START_BYTE_INDICATOR] - DBC_START_BYTE;
  printf("Data Block Collection Size: %d bytes\n", dbc_size);

  parse_data_block_collection(&extension_block[DBC_START_BYTE], dbc_size);

  return 0;
}

int parse_data_block_collection(const uint8_t* dbc, int dbc_size) {
  const uint8_t DATA_BLOCK_SIZE_MASK = 0x1FU; // Bits 4-0
  const uint8_t DATA_BLOCK_TYPE_RSH = 5U; // Right shift by 5 to get bits 7-5

  uint8_t block_i = 0;
  uint8_t byte_i = 0;

  // Loop for each data block
  while (byte_i < dbc_size) { // "while" used instead of "for" b/c block_size changes every iteration
    // Parse and print header information
    data_block_type_t block_type = dbc[byte_i] >> DATA_BLOCK_TYPE_RSH; // Identify each individual data block within the DBC by their tag
    uint8_t block_size = dbc[byte_i] & DATA_BLOCK_SIZE_MASK; // Size of data block in bytes
    printf("----Data Block %d----\n", block_i);
    printf("Size: %d bytes\n", (block_size + 1)); // + 1 to include the header

    // Parse and print corresponding data block type and contained data
    byte_i += 1; // Step index to first data byte. Preps the switch statement to read the extended data block type in byte 1 if block_type = 0b111
    printf("Type: ");
    switch(block_type) {
      case DB_TYPE_AUDIO:
        printf("Audio (ADB)\n");
        parse_data_block_audio(&dbc[byte_i], block_size); // Passing the address of the start byte still passes the actual array, but starting at byte_i where the data begins
        break;
      case DB_TYPE_VIDEO: printf("Video (VDB)\n"); break;
      case DB_TYPE_VSDB: printf("Vendor Specific Data Block (VSDB)\n"); break;
      case DB_TYPE_SADB: printf("Speaker Allocation (SADB)\n"); break;
      case DB_TYPE_VESA_DTC: printf("VESA Display Transfer Characteristic (VESA DTCDB)\n"); break;
      case DB_TYPE_VFDB: printf("Video Format (VFDB)\n"); break;
      case DB_TYPE_EXTENDED: printf("Extended\n"); break;
      default: printf("Unexpected Data\n"); break;
    }

    // Move to next data block
    block_i += 1;
    byte_i += block_size;
  }

  return 0;
}

int parse_data_block_audio(const uint8_t* data, int block_size) {
  const uint8_t SAD_FORMAT_RSH = 3U; // Right shift by 3 to get bits 7-3. Bit 7 is reserved 0, thus format code is contained in bits 6-3
  const uint8_t SAD_BITRATE_FACTOR = 8U; // kilobits per second conversion factor to get bitrate in byte 3 of the SAD

  for (uint8_t byte_i = 0; byte_i < block_size; ++byte_i) {
    // SAD Byte 0
    sad_format_t sad_format = data[byte_i] >> SAD_FORMAT_RSH;
    printf("Audio Format: ");
    switch(sad_format) {
      case SAD_FORMAT_LPCM: printf("Linear Pulse-Code Modulation (LPCM)\n"); break;
      case SAD_FORMAT_AC_3: printf("Dolby Audio Codec 3 (AC-3)\n"); break;
      case SAD_FORMAT_MPEG_1: printf("MPEG-1\n"); break;
      case SAD_FORMAT_MP3: printf("MP3\n"); break;
      case SAD_FORMAT_MPEG_2: printf("MPEG-2\n"); break;
      case SAD_FORMAT_AAC_LC: printf("Advanced Audio Coding, Low-Complexity (AAC-LC)\n"); break;
      case SAD_FORMAT_DTS: printf("Digital Theater Systems, Inc. (DTS)\n"); break;
      case SAD_FORMAT_ATRAC: printf("Adaptive Transform Acoustic Coding (ATRAC)\n"); break;
      case SAD_FORMAT_DSD: printf("Direct Stream Digital (DSD)\n"); break;
      case SAD_FORMAT_DD_PLUS: printf("Dolby Digital Plus (DD+)\n"); break;
      case SAD_FORMAT_DTS_HD: printf("DTS-HD\n"); break;
      case SAD_FORMAT_DOLBY_MAT: printf("Dolby Metadata-enhanced Audio Transmission (Dolby MAT)\n"); break;
      case SAD_FORMAT_DST_AUDIO: printf("Direct Stream Transfer Audio Compression Protocol (DST Audio)\n"); break;
      case SAD_FORMAT_MS_WMA_PRO: printf("Microsoft WMA Pro\n"); break;
      case SAD_FORMAT_EXTENDED: printf("Extended\n"); break; // Extended audio format code found in byte 3, bits 7-3
      default: printf("Unexpected Data\n"); break;
    }
    uint8_t channels = (data[byte_i] & SAD_CHANNEL_MASK) + 1; // Number of channels is 1-8 where 0b000 = 1
    printf("Supported Maximum Channels: %d\n", channels);

    // SAD Byte 1
    byte_i += 1;
    uint8_t sad_sample_freq_data = data[byte_i];
    printf("Supported Sample Frequencies (kHz): ");
    if (sad_sample_freq_data & BIT_6_MASK) printf("192 "); // Bit 6
    if (sad_sample_freq_data & BIT_5_MASK) printf("176 "); // Bit 5
    if (sad_sample_freq_data & BIT_4_MASK) printf("96 "); // Bit 4
    if (sad_sample_freq_data & BIT_3_MASK) printf("88 "); // Bit 3
    if (sad_sample_freq_data & BIT_2_MASK) printf("48 "); // Bit 2
    if (sad_sample_freq_data & BIT_1_MASK) printf("44.1 "); // Bit 1
    if (sad_sample_freq_data & BIT_0_MASK) printf("32 "); // Bit 0
    printf("\n");

    // SAD Byte 2
    byte_i += 1;
    if (sad_format == SAD_FORMAT_LPCM) {
      uint8_t sad_bit_depth = data[byte_i];
      printf("Supported Bit Depths (bit): ");
      if (sad_bit_depth & BIT_2_MASK) printf("24 "); // Bit 2
      if (sad_bit_depth & BIT_1_MASK) printf("20 "); // Bit 1
      if (sad_bit_depth & BIT_0_MASK) printf("16 "); // Bit 0
      printf("\n");
    }
    else if (sad_format >= SAD_FORMAT_AC_3 && sad_format <= SAD_FORMAT_ATRAC) {
      int bitrate = data[byte_i] * SAD_BITRATE_FACTOR;
      printf("Maximum Supported Bitrate: %d kbps\n", bitrate);
    }
    else if (sad_format >= SAD_FORMAT_DSD && sad_format <= SAD_FORMAT_MS_WMA_PRO) {
      printf("Bit Depth / Bitrate Information: Unsupported for this format\n");
    }
  }

  return 0;
}

int write_edid(uint8_t* edid, const uint8_t byte_value, const uint8_t byte_i) {
  printf("Writing value 0x%02x to byte %d...\n", byte_value, byte_i);

  edid[byte_i] = byte_value;
  printf("  Write Complete\n\n");

  return 0;
}

uint8_t set_bits(const uint8_t mask, uint8_t old_value, uint8_t new_value) {
  return (~mask & old_value) | (mask & new_value);
}
