/* t-keyb.c

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

__attribute__((naked)) __attribute__((section(".start_section")))
void startup(void)
{
    asm volatile (" LDR R0,=0x2001C000\n"   /* set stack */
                  " MOV SP,R0\n"
                  " BL main\n"              /* call main */
                  ".L1: B .L1\n");          /* never return */
}

#include "keypad.h"
#include "debug.h"

int main(void)
{
    keypad kp;
    char key;
    char str[] = " \n";


    // Connect the keypad to GPIO_D (HIGH)
    keypad_connect(&kp, GPIO_D, true);

    while (true)
    {
        key = keypad_read(&kp);

        if (key)
        {
            str[0] = key;
            printc(str);
        }
    }

    return 0;
}
