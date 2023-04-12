/* time.h

Copyright (C) 2023  Albin Ahlbäck

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef TIME_H
#define TIME_H

#include "types.h"

typedef volatile struct
{
    union
    {
        uint32_t control;
        struct
        {
            unsigned enable     : 1;
            unsigned interupt   : 1;
            unsigned source     : 1;
            unsigned _reserved  : 13;
            unsigned count      : 1;
            unsigned _reserved2 : 15;
        };
    };
    union
    {
        uint32_t load_full;
        struct
        {
            unsigned load           : 24;
            unsigned _reserved_load : 8;
        };
    };
    union
    {
        uint32_t value_full;
        struct
        {
            unsigned value           : 24;
            unsigned _reserved_value : 8;
        };
    };
    union
    {
        uint32_t calib_full;
        struct
        {
            unsigned tenms           : 24;
            unsigned _reserved_tenms : 6;
            unsigned skew            : 1;
            unsigned noref           : 1;
        };
    };
}
SYSTICK, * PSYSTICK;

#define STK ((PSYSTICK) 0xE000E010)

void delay_250ns(void)
{
    STK->control = 0;
    STK->load    = (168 / 4) - 1;
    STK->value   = 0;
    STK->control = 5;
    while (STK->count == 0)
        ;
    STK->control = 0;
}

void delay_nano(uint32_t ns)
{
    STK->control = 0;
    STK->load    = 6 * ns; // 5.9 ~ 6
    STK->value   = 0;
    STK->control = 5;
    while (STK->count == 0)
        ;
    STK->control = 0;
}

void delay_micro(uint32_t us)
{
    while (us > 0)
    {
        delay_250ns();
        delay_250ns();
        delay_250ns();
        delay_250ns();
        us--;
    }
}

void delay_milli(uint32_t ms)
{
    while (ms > 0)
    {
#ifndef SIMULATOR
        delay_micro(1000);
#else
        delay_micro(1);
#endif
        ms--;
    }
}

#endif /* TIME_H */
