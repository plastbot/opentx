/*
 * Authors (alphabetical order)
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Jean-Pierre Parisy
 * - Karl Szmutny <shadow@privy.de>
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Romolo Manfredini <romolo.manfredini@gmail.com>
 * - Thomas Husterer
 *
 * open9x is based on code named
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

#include "open9x.h"

#if defined(PCBARM)
void hapticOff()
{
	PWM->PWM_DIS = PWM_DIS_CHID2 ;						// Disable channel 2
	PWM->PWM_OOV &= ~0x00040000 ;	// Force low
	PWM->PWM_OSS |= 0x00040000 ;	// Force low
}

// pwmPercent 0-100
void hapticOn( uint32_t pwmPercent )
{
	register Pwm *pwmptr ;

	pwmptr = PWM ;

	if ( pwmPercent > 100 )
	{
		pwmPercent = 100 ;		
	}
	pwmptr->PWM_CH_NUM[2].PWM_CDTYUPD = pwmPercent ;		// Duty
	pwmptr->PWM_ENA = PWM_ENA_CHID2 ;						// Enable channel 2
	pwmptr->PWM_OSC = 0x00040000 ;	// Enable output
}
#endif



hapticQueue::hapticQueue()
{
  buzzTimeLeft = 0;
  buzzPause = 0;

  t_queueRidx = 0;
  t_queueWidx = 0;

  hapticTick = 0;
}

void hapticQueue::heartbeat()
{
#if defined(SIMU)
  return;
#endif

  if (buzzTimeLeft > 0) {
    buzzTimeLeft--; // time gets counted down
#if defined(PCBARM)
    hapticOn(g_eeGeneral.hapticStrength * 20);
#else
    if (hapticTick-- > 0) {
      HAPTIC_ON; // haptic output 'high'
    }
    else {
      HAPTIC_OFF; // haptic output 'high'
      hapticTick = g_eeGeneral.hapticStrength;
    }
#endif
  }
  else {
    HAPTIC_OFF; // haptic output 'high'
    if (buzzPause > 0) {
      buzzPause--;
    }
    else if (t_queueRidx != t_queueWidx) {
      buzzTimeLeft = queueHapticLength[t_queueRidx];
      buzzPause = queueHapticPause[t_queueRidx];
      if (!queueHapticRepeat[t_queueRidx]--) {
        t_queueRidx = (t_queueRidx + 1) % HAPTIC_QUEUE_LENGTH;
      }
    }
  }
}

void hapticQueue::play(uint8_t tLen, uint8_t tPause, uint8_t tFlags)
{
  tLen = getHapticLength(tLen);

  if (tFlags & PLAY_NOW || (!busy() && empty())) {
    buzzTimeLeft = tLen;
    buzzPause = tPause;
    t_queueWidx = t_queueRidx;
  }
  else {
    tFlags += 1;
  }

  tFlags &= 0x0f;
  if (tFlags) {
    uint8_t next_queueWidx = (t_queueWidx + 1) % HAPTIC_QUEUE_LENGTH;
    if (next_queueWidx != t_queueRidx) {
      queueHapticLength[t_queueWidx] = tLen;
      queueHapticPause[t_queueWidx] = tPause;
      queueHapticRepeat[t_queueWidx] = tFlags-1;
      t_queueWidx = next_queueWidx;
    }
  }
}

void hapticQueue::event(uint8_t e)
{
  if (g_eeGeneral.hapticMode>0 || (g_eeGeneral.hapticMode==0 && e>=AU_WARNING1) || (g_eeGeneral.hapticMode>=-1 && e<=AU_ERROR)) {
    switch (e) {
      case 0: // very little buzz for keys / trims
        play(5, 0, PLAY_NOW);
        break;
      case AU_TIMER_20: // two buzz
        play(10,2,1);
        break;
      case AU_TIMER_30: // three buzz
        play(10,2,2);
        break;
      default:
        play(10,2,0);
        break;
    }
  }
}

hapticQueue haptic;

