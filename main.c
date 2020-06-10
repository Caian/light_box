/*
 * Copyright (C) 2020 Caian Benedicto <caianbene@gmail.com>
 *
 * This file is part of light_box.
 *
 * light_box is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * light_box is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with light_box.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <msp430.h>
#include "ws2812.h"
#include "animations.h"

#define HALF_BLINK 1600000
#define FULL_BLINK 2*HALF_BLINK

void blinkOne()
{
    P1OUT &= ~BIT0;
    __delay_cycles(HALF_BLINK);
    P1OUT |= BIT0;
    __delay_cycles(FULL_BLINK);
    P1OUT &= ~BIT0;
    __delay_cycles(HALF_BLINK);
}

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT

    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    if (CALBC1_16MHZ==0xFF)    // If calibration constant erased
    {
        while(1);              // do not load, trap CPU!!
    }

    // configure clock to 16 MHz
    BCSCTL1 = CALBC1_16MHZ;    // DCO = 16 MHz
    DCOCTL = CALDCO_16MHZ;

    // Configure buttons
    P1DIR &= ~(BIT3 | BIT4 | BIT5);
    P1OUT |= (BIT3 | BIT4 | BIT5);
    P1REN |= (BIT3 | BIT4 | BIT5);

    // Initialize LED strip
    blinkOne();
    initStrip();

    // Main loop
    while (1)
    {
        if ((P1IN & BIT3) == 0)
        {
            P1OUT &= ~BIT0;
            __delay_cycles(32000000); // 2s delay
            sunrise();
        }

        if ((P1IN & BIT4) == 0)
        {
            P1OUT &= ~BIT0;
            __delay_cycles(32000000); // 2s delay
            sunset();
        }

        if ((P1IN & BIT5) == 0)
        {
            P1OUT &= ~BIT0;
            __delay_cycles(32000000); // 2s delay
            nightshow();
        }

        P1OUT |= BIT0;
    }
}
