// SquachWatch-CYD — TFT_eSPI user setup for the NiceMCU-32S-DEV_2.8IPS
// board (github.com/NiceMCU-01/NiceMCU-32S-DEV_2.8IPS), sold with an
// "XH-32S" module — a plain single-core-labeled ESP32-WROOM-class part,
// not an S2/S3/C-series chip; platformio.ini still targets board=esp32dev.
//
// Confirmed against that repo's include/nicemcu/board_config.h and tested
// on the project owner's physical board; see [env:cyd-nicemcu] in
// platformio.ini for the build target.
//
// Same panel silicon as [env:cyd] (ST7789, 240x320) but a DIFFERENT
// pinout from every other board this project supports:
//   - DC and RST are swapped relative to the standard CYD pinout
//     (DC=2/no-RST there; here DC=12/RST=2).
//   - RST is wired and shared between the panel AND the capacitive
//     touch controller (one reset line for both), unlike the
//     JC2432W328C variant's separate CAP_RST=25.
//   - No MISO pin at all -- this board's bus is write-only.
//   - Backlight is GPIO25, not GPIO21/27.
// See the NICEMCU-specific blocks in main.cpp (search "NICEMCU") for
// the CAP_RST and backlight-channel changes this pinout requires.
#pragma once

#define USER_SETUP_INFO    "SquachWatch-CYD / NiceMCU-32S-DEV 2.8in / ST7789"
#define ST7789_DRIVER
// Portrait native, same as env:cyd. Rotated to landscape at runtime.
#define TFT_WIDTH   240
#define TFT_HEIGHT  320
#define TFT_ROTATION 1

// SPI pins (NiceMCU-32S-DEV_2.8IPS board_config.h)
// No TFT_MISO -- this board's display bus has no data line back to the
// MCU; TFT_eSPI works fine without one (it just can't read the panel).
#define TFT_MOSI  13
#define TFT_SCLK  14
#define TFT_CS    15
#define TFT_DC    12
#define TFT_RST    2   // Shared with the capacitive touch controller's
                       // reset line -- TFT_eSPI pulses this during
                       // tft.init(), which resets touch too. See the
                       // CAP_RST override in main.cpp: do NOT also
                       // pulse this pin a second time as a touch reset.
#define TFT_BL    25

// Backlight
#define TFT_BACKLIGHT_ON   1
#define PWM_FREQ           5000
#define PWM_MAX_DUTY       255

// SPI frequency. Starting at the same conservative 40MHz as env:cyd
// rather than assuming this board tolerates the 80MHz overclock --
// nobody has measured trace quality on it yet.
#ifndef SPI_FREQUENCY
#define SPI_FREQUENCY         40000000
#endif
#define SPI_READ_FREQUENCY    20000000

// Fonts -- identical to env:cyd; nothing about fonts is board-specific.
#define LOAD_GLCD
#define LOAD_FONT2

// Colour polarity/order: copied from env:cyd's ST7789 header as a
// starting guess (same driver IC family). If colours come out wrong
// (inverted, or red/blue swapped) on real hardware, flip
// TFT_INVERSION_OFF to TFT_INVERSION_ON and/or TFT_RGB_ORDER to
// TFT_RGB, the same way cyd_user_setup.h's own comment describes for
// its ILI9341 sibling.
#define TFT_RGB_ORDER TFT_BGR
