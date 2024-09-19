# embedded-systems-design-basics
Repository of lab projects demonstrating the basics of embedded systems design on the STM32 platform. Topics covered include: GPIO, interrupts, timers, DMA, PWM, common communication protocols, and RTOS.

### Compilation
When writing and compiling programs such as those in Lab 0:
* Ensure that every C file contains an `#include` for all necessary correct local and standard header files
* Ensure all necessary local C files are listed in the compilation argument, such as `gcc -o program main.c module.c`
* Use include guards such as the more modern and widely supported `#pragma once` or the officially supported `#ifndef FILENAME_H #define FILENAME_H #endif`
