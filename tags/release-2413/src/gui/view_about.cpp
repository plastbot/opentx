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

#include "../opentx.h"

#if defined(PCBTARANIS)
  const pm_uchar about_bmp[] PROGMEM = {
  #include "../bitmaps/about.lbm"
  };
#endif

enum AboutScreens {
  ABOUT_OPENTX,
  ABOUT_BERTRAND,
  ABOUT_MIKE,
  ABOUT_ROMOLO,
  ABOUT_ANDRE,
  ABOUT_ROB,
  ABOUT_MARTIN,
  ABOUT_HARDWARE,
  ABOUT_PARENTS,
  ABOUT_END,
  ABOUT_COUNT,
};

void menuAboutView(uint8_t event)
{
  static int screenIndex;
  static int greyIndex;

  switch(event)
  {
    case EVT_ENTRY:
      screenIndex = 0;
      greyIndex = 0;
      break;
    case EVT_KEY_FIRST(KEY_DOWN):
      screenIndex < ABOUT_PARENTS ? screenIndex++ : screenIndex = ABOUT_OPENTX;
      greyIndex = 0;
      break;
    case EVT_KEY_FIRST(KEY_UP):
      screenIndex > ABOUT_OPENTX ? screenIndex-- : screenIndex = ABOUT_PARENTS;
      greyIndex = 0;
      break;
    case EVT_KEY_FIRST(KEY_EXIT):
      chainMenu(menuMainView);
    return;
  }

  lcd_bmp(0, 0, about_bmp);
  lcd_putsAtt(64, 0, STR_ABOUTUS, DBLSIZE);
  lcd_hline(62, 18, 120);
  lcd_hline(62, 19, 130, GREY_DEFAULT);

  LcdFlags att = GREY(max(0, 15-greyIndex/2));
  int screenDuration = 150;

  switch (screenIndex) {
    case ABOUT_OPENTX:
    case ABOUT_END:
      lcd_putsAtt(62, 22, STR_ABOUT_OPENTX_1, SMLSIZE);
      lcd_putsAtt(62, 30, STR_ABOUT_OPENTX_2, SMLSIZE);
      lcd_putsAtt(62, 38, STR_ABOUT_OPENTX_3, SMLSIZE);
      lcd_putsAtt(62, 46, STR_ABOUT_OPENTX_4, SMLSIZE);
      lcd_putsAtt(62, 54, STR_ABOUT_OPENTX_5, SMLSIZE);
      screenDuration = 300;
      break;

    case ABOUT_BERTRAND:
      lcd_putsAtt(62, 24, STR_ABOUT_BERTRAND_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_BERTRAND_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_BERTRAND_3, att|SMLSIZE);
      break;

    case ABOUT_MIKE:
      lcd_putsAtt(62, 24, STR_ABOUT_MIKE_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_MIKE_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_MIKE_3, att|SMLSIZE);
      lcd_putsAtt(67, 52, STR_ABOUT_MIKE_4, att|SMLSIZE);
      break;

    case ABOUT_ROMOLO:
      lcd_putsAtt(62, 24, STR_ABOUT_ROMOLO_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_ROMOLO_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_ROMOLO_3, att|SMLSIZE);
      break;

    case ABOUT_ANDRE:
      lcd_putsAtt(62, 24, STR_ABOUT_ANDRE_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_ANDRE_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_ANDRE_3, att|SMLSIZE);
      break;

    case ABOUT_ROB:
      lcd_putsAtt(62, 24, STR_ABOUT_ROB_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_ROB_2, att|SMLSIZE);
      break;

    case ABOUT_MARTIN:
      lcd_putsAtt(62, 24, STR_ABOUT_MARTIN_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_MARTIN_2, att|SMLSIZE);
      break;

    case ABOUT_HARDWARE:
      lcd_putsAtt(62, 24, STR_ABOUT_HARDWARE_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_HARDWARE_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_HARDWARE_3, att|SMLSIZE);
      screenDuration = 300;
      break;

    case ABOUT_PARENTS:
      lcd_putsAtt(62, 24, STR_ABOUT_PARENTS_1, att);
      lcd_putsAtt(68, 36, STR_ABOUT_PARENTS_2, att|SMLSIZE);
      lcd_putsAtt(68, 44, STR_ABOUT_PARENTS_3, att|SMLSIZE);
      lcd_putsAtt(67, 52, STR_ABOUT_PARENTS_4, att|SMLSIZE);
      screenDuration = 300;
      break;
  }

  if (++greyIndex == screenDuration) {
    greyIndex = 0;
    if (++screenIndex == ABOUT_COUNT) {
      chainMenu(menuMainView);
    }
  }
}