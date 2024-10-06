# Bit Set/Reset Register (BSRR)
* Setting the first 16 bits high (0x0000_FFFF) will sets those pins.
* Setting the last 16 bits high (0xFFFF_0000) will resets those pins.
* Bit Set takes priority over Bit Reset if they are conflicted.
