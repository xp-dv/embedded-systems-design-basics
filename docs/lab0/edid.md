# The VESA Extended Display Identification Data (EDID) Standard
## Base Block
* The first 128 bytes (bytes 0-127) make up the EDID Base Block.
* The last 128 bytes (bytes 128-255) make up the CTA Extension Block based on the CTA 861 std.
* Bytes 0-7 are always the fixed header pattern "0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00".
* Video Interface Type (Digital or Analog) at byte 20, bit 7.
* Video Interface Standard (HDMI, DVI, etc) at Byte 20, bits 0-4.
* The last byte, byte 127, is always a checksum. Checksums are calculated when the EDID is generated.
## CTA Extension Block
* Byte 128 of the EDID (byte 0 of the CTA Extension Block) is the Extension Tag. Always 0x02 for CTA Extension Blocks.
* Byte 1 of the CTA Extension Block (Byte 129 of the EDID) is the CTA Extension Block revision number.
* Byte 2 of the CTA Extension Block (Byte 130 of the EDID) is the byte # within the CTA Extension Block at which the Detailed Timing Descriptor (DTD) information begins.
* The last byte of the CTA Extension Block, byte 255 of the EDID, is always a checksum. Checksums are calculated when the EDID is generated.
## Data Block Collection (DBC)
* Bytes 4 to (value of byte 2 minus 1) of the CTA Extension Block make up the DBC.
* If byte 2 = 0x00, the DBC makes up the rest of the CTA Extension Block. If byte 2 = 0x04, the rest of the CTA Extension Block consists of DTDs.
* Byte 4 of the DBC is the first byte (byte 0) of the first Data Block (DB), and the first byte of every Data Block afterwards (until the byte given in DBC byte 2) will be a Data Block header.
* Within the DBC, byte 0 of every Data Block is the Data Block header. Bits 7-5 indicate Data Block type. If Data Block type = 0b111, use the extended Data Block type indicator in byte 1. Bits 4-0 indicate # of remaining bytes in this block after byte 0.
## Audio Data Blocks (ADBs)
* A Data Block with a Block Type Tag of 0b001 (bits 7-5 of the Data Block header at byte 0) is an Audio Data Block (ADB).
* Audio Data Blocks consist of one or more 3-byte Short Audio Descriptors (SADs) after the Data Block header at byte 0.
* SAD byte 0, bit 7 is reserved 0, bits 6-3 indicate audio format, bits 2-0 indicate the maximum supported number of channels.
* SAD byte 1, bit 7 is reserved 0, bits 6-0 indicate the supported sampling freqencies with each bit representing a single frequency in kHz.
* SAD byte 2 is format dependent:
  * For audio format code 1 (LPCM), bits 7-3 are reserved, and bits 2-0 indicate the supported bit-depths with each bit representing a single bit-depth.
  * For audio format codes 2-8, byte 3 represents bitrate in kbps divided by 8 and vice-versa (i.e. byte 3 times 8 will give the bitrate in kbps).
  * For audio format codes 9-14, its even more specific to the format and is too complex to cover here.
  * For audio format code 15 (Extended), bits 7-3 represent the extended audio format code (most of the extended codes refer to different versions of MPEG-4). Bits 2-0 are format dependent.
