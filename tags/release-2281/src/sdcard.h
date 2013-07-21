/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef sdcard_h
#define sdcard_h

#include "FatFs/ff.h"

#ifdef SIMU
#define ROOT_PATH    "."
#define MODELS_PATH  "."
#define LOGS_PATH    "."
#define SOUNDS_PATH  "."
#define SYSTEM_SOUNDS_PATH "."
#define BITMAPS_PATH  "."
#else
#define ROOT_PATH           "/"
#define MODELS_PATH         "/MODELS"
#define LOGS_PATH           "/LOGS"   // no trailing slash = important
#define SOUNDS_PATH         "/SOUNDS" // no trailing slash = important
#define SYSTEM_SOUNDS_PATH  SOUNDS_PATH "/SYSTEM" // no trailing slash = important
#define BITMAPS_PATH        "/BMP"
#endif

#define MODELS_EXT   ".bin"
#define LOGS_EXT     ".csv"
#define SOUNDS_EXT   ".wav"
#define BITMAPS_EXT  ".bmp"

extern FATFS g_FATFS_Obj;

extern uint8_t logDelay;
extern const pm_char * openLogs();
extern void closeLogs();
extern void writeLogs();

inline const pm_char *SDCARD_ERROR(FRESULT result)
{
  if (result == FR_NOT_READY)
    return STR_NO_SDCARD;
  else
    return STR_SDCARD_ERROR;
}

#if defined(PCBTARANIS)
  #define O9X_FOURCC 0x3378396F // o9x for Taranis
#elif defined(PCBSKY9X)
  #define O9X_FOURCC 0x3278396F // o9x for sky9x
#elif defined(PCBGRUVIN9X)
  #define O9X_FOURCC 0x3178396F // o9x for gruvin9x
#endif

#endif
