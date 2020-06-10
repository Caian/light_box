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

void setLayer(int layer, u_char r, u_char g, u_char b)
{
    int i;
    for (i = 0; i < 10; i++)
        setLEDColor(10*layer + i, r, g, b);
}

void setSkyLayer   (u_char r, u_char g, u_char b) { setLayer(0, r, g, b); }
void setCity2Layer (u_char r, u_char g, u_char b) { setLayer(1, r, g, b); }
void setCity1Layer (u_char r, u_char g, u_char b) { setLayer(2, r, g, b); }
void setTowerLayer (u_char r, u_char g, u_char b) {
    int i, layer;
    u_char r2, g2, b2;
    layer = 3;
    for (i = 0; i < 10; i++)
    {
        // Make lights brighter around the eiffel tower
        if (i == 1 || i == 2 || i == 3 || i == 4)
        {
            int temp;
            temp = r; temp *= 14; temp /= 10; r2 = temp;
            temp = g; temp *=  4; temp /= 10; g2 = temp;
            temp = b; temp *=  4; temp /= 10; b2 = temp;
            //g2 = g;
            //b2 = b;
        }
        else
        {
            r2 = r;
            g2 = g;
            b2 = b;
        }
        setLEDColor(10*layer + i, r2, g2, b2);
    }
}
void setGrass2Layer(u_char r, u_char g, u_char b) {
    int i, layer;
    u_char r2, g2, b2;
    layer = 4;
    for (i = 0; i < 10; i++)
    {
        // Make lights redder around the bicycle (todo pinker?)
        if (i == 4 || i == 5 || i == 6 || i == 7)
        {
            int temp;
            temp = r; temp *= 14; temp /= 10; r2 = temp;
            //temp = g; temp *=  3; temp /= 10; g2 = temp;
            //temp = b; temp *= 14; temp /= 10; b2 = temp;
            g2 = g;
            b2 = r2;
        }
        else
        {
            r2 = r;
            g2 = g;
            b2 = b;
        }
        setLEDColor(10*layer + i, r2, g2, b2);
    }
}
void setGrass1Layer(u_char r, u_char g, u_char b) { setLayer(5, r, g, b); }

int sunrise()
{
    int i, r, g, b;

    for (i = 0; i <= 200; i++)
    {
        r = 0;
        g = 0;
        b = 0;
        setSkyLayer(r, g, b);
        r = i/5;
        g = i/15;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        r = i/5;
        g = i/10;
        b = 0;
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    __delay_cycles(32000000); // 2s delay
    for (i = 0; i <= 200; i++)
    {
        r = i/2;
        g = i/20;
        b = 0;
        setSkyLayer(r, g, b);
        r = 40 - i/5;
        g = 13 - i/15;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        r = 40 - i/5;
        g = 20 - i/10;
        b = 0;
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    __delay_cycles(32000000); // 2s delay
    for (i = 0; i <= 100; i++)
    {
        r = 100 - i/2;
        g = 10 + i/5*2;
        b = i/2;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    for (i = 0; i <= 200; i++)
    {
        r = 50 - i/10;
        g = 50 + i/2;
        b = 50 + i/2;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    __delay_cycles(32000000); // 2s delay
    for (i = 0; i <= 200; i++)
    {
        r = 30 - i/20*3;
        g = 150 - i/4*3;
        b = 150 - i/4*3;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }

    return 0;
}

int sunset()
{
    int i, r, g, b;

    for (i = 0; i <= 200; i++)
    {
        r = i/20*3;
        g = i/4*3;
        b = i/4*3;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    __delay_cycles(32000000); // 2s delay
    for (i = 0; i <= 200; i++)
    {
        r = 30 + i/20*7;
        g = 150 - i/2;
        b = 150;
        setSkyLayer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    for (i = 0; i <= 200; i++)
    {
        r = 100;
        g = 50 - i/10;
        b = 150 - i/4*3;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    for (i = 0; i <= 200; i++)
    {
        r = 100 - i/2;
        g = 30 - i/17*3;
        g = g < 0 ? 0 : g;
        b = 0;
        setSkyLayer(r, g, b);
        r = 0;
        g = 0;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    for (i = 0; i <= 200; i++)
    {
        r = 0;
        g = 0;
        b = 0;
        setSkyLayer(r, g, b);
        r = i/5;
        g = i/15;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        r = i/5;
        g = i/10;
        b = 0;
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }
    __delay_cycles(32000000); // 2s delay
    for (i = 0; i <= 200; i++)
    {
        r = 0;
        g = 0;
        b = 0;
        setSkyLayer(r, g, b);
        r = 40 - i/5;
        g = 13 - i/15;
        b = 0;
        setCity2Layer(r, g, b);
        setCity1Layer(r, g, b);
        setTowerLayer(r, g, b);
        r = 40 - i/5;
        g = 20 - i/10;
        b = 0;
        setGrass2Layer(r, g, b);
        setGrass1Layer(r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }

    return 0;
}

int nightshow()
{
    static const int MAXL = 199;
    int i, j, k, m, r, g, b, start;

    r = 0;
    g = 0;
    b = 0;
    setSkyLayer(r, g, b);
    setCity2Layer(r, g, b);
    setCity1Layer(r, g, b);
    setTowerLayer(r, g, b);
    setGrass2Layer(r, g, b);
    setGrass1Layer(r, g, b);

    start = 30;
    for (m = 0; m < 2; m++)
    {
        for (i = 0; i < 6*(MAXL+1); i++)
        {
            j = i / (MAXL+1);
            k = i % (MAXL+1);

            switch (j)
            {
            case 0:
                r = MAXL;
                g = k;
                b = 0;
                break;
            case 1:
                r = MAXL - k;
                g = MAXL;
                b = 0;
                break;
            case 2:
                r = 0;
                g = MAXL;
                b = k;
                break;
            case 3:
                r = 0;
                g = MAXL - k;
                b = MAXL;
                break;
            case 4:
                r = k;
                g = 0;
                b = MAXL;
                break;
            case 5:
                r = MAXL;
                g = 0;
                b = MAXL-k;
                break;
            }

            setLEDColor(start + 6, r, g, b);
            //setLEDColor(start + 7, r, g, b);
            setLEDColor(start - 10 + 2, r, g, b);
            //setLEDColor(start - 10 + 3, r, g, b);
            showStrip();
            __delay_cycles(160000); // 10ms delay
        }
    }

    for (i = 0; i <= MAXL; i++)
    {
        r = MAXL - i;
        g = 0;
        b = 0;
        setLEDColor(start + 6, r, g, b);
        //setLEDColor(start + 7, r, g, b);
        setLEDColor(start - 10 + 2, r, g, b);
        //setLEDColor(start - 10 + 3, r, g, b);
        showStrip();
        __delay_cycles(160000); // 10ms delay
    }

    return 0;
}
