/* t-7seg.c

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

#include "7seg.h"
#include "gpio.h"
#include "time.h"

__attribute__((naked)) __attribute__((section(".start_section")))
void
startup(void)
{
    asm volatile (" LDR R0,=0x2001C000\n"   /* set stack */
                  " MOV SP,R0\n"
                  " BL main\n"              /* call main */
                  ".L1: B .L1\n");          /* never return */
}

int main(void)
{
    SEVENSEG seg;
    sevenseg_connect(&seg, GPIO_D);
    uint8_t chs[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    size_t len = sizeof(chs) / sizeof(uint8_t);
    uint8_t i  = 0;

    while (true)
    {
        sevenseg_write(&seg, chs[i]);
        delay_milli(800);
        i++;
        i %= len;
    }

    return 0;
}
