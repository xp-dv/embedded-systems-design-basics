# Embedded Systems Design Basics
Repository of lab projects demonstrating the basics of embedded systems design on the STM32 platform in C. Topics covered include: C programming review, GPIO, interrupts, timers, DMA, PWM, common communication protocols, and RTOS.

## Style Guide
All of the code in this repository roughly follows STMicroelectronics Product Line Marketing Manager, Tilen Majerle's [C Code Style Guide](https://github.com/MaJerle/c-code-style).

## Docs
Background information and notes for each lab may be found in [docs](/docs).

## Compilation
When writing and compiling programs such as those in Lab 0:
* Ensure that every C file contains an `#include` for all necessary correct local and standard header files.
* Ensure all necessary local C files are listed in the compilation argument, such as `gcc -o program main.c module.c`.
* Use include guards such as the more modern and widely supported `#pragma once` or the officially supported `#ifndef FILENAME_H #define FILENAME_H #endif`.
