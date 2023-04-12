/* keypad.h

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

#ifndef KEYPAD_H
#define KEYPAD_H

#include "gpio.h"
#include "types.h"

/*
    Keypad driver for the MD407
    Key mapping:
    1 2 3 A
    4 5 6 B
    7 8 9 C
    * 0 # D
    The 4 rows are set to output and the 4 columns are set to input.
    The columns are set to pull-up and the rows are set to high speed.
    When a key is pressed, the corresponding column will be pulled down.

    The keypad is connected to GPIOE or GPIOD ( upper or lower )
*/

#define _KEYPAD_ASSIGN_REGISTERS(NAME, TYPE, I)                         \
do                                                                      \
{                                                                       \
    self->_##NAME =                                                     \
        ((TYPE *) ((char *) &self->_port->NAME + sizeof(TYPE) * (I)));  \
}                                                                       \
while (0)

#define KEYPAD_NULL_KEY ((char) 0)

// Defualt key mapping
static char KEYPAD_MAP[4][4] = {{'1', '2', '3', 'A'},
                                {'4', '5', '6', 'B'},
                                {'7', '8', '9', 'C'},
                                {'*', '0', '#', 'D'}};

typedef volatile struct
{
    PGPIO _port;
    uint16_t *_moder;
    uint8_t *_otyper;
    uint16_t *_ospeedr;
    uint16_t *_pupdr;
    uint8_t *_idr;
    uint8_t *_odr;
    char (* map)[4][4];
}
keypad;

/* Initialize keypad driver */
void keypad_connect(keypad * self, PGPIO port, boolean high_port)
{
    /* Start the clock for the GPIO D & E ports */
    *((unsigned long *) 0x40023830) = 0x18;

    self->_port = port; /* Assign the port base */
    self->map = &KEYPAD_MAP; /* Assign default keymap */

    /* Assign each register pins to the keypad */
    _KEYPAD_ASSIGN_REGISTERS(moder, uint16_t, high_port);
    _KEYPAD_ASSIGN_REGISTERS(otyper, uint8_t, high_port);
    _KEYPAD_ASSIGN_REGISTERS(ospeedr, uint16_t, high_port);
    _KEYPAD_ASSIGN_REGISTERS(pupdr, uint16_t, high_port);
    _KEYPAD_ASSIGN_REGISTERS(idr, uint8_t, high_port);
    _KEYPAD_ASSIGN_REGISTERS(odr, uint8_t, high_port);

    /* Configure the pins */
    *self->_moder = 0x5500; /* Set output pins to high and input pins to low */
    *self->_otyper = 0x0000; /* Set the output type to push-pull */
    *self->_ospeedr = 0x5555; /* Set the speed to high */
    *self->_pupdr = 0x0066; /* Set the input type to pull-up */
}

/* Return currently pressed key. If non is pressed, return KEYPAD_NULL_KEY. */
char keypad_read(keypad * self)
{
    *self->_odr = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        *self->_odr = 0x10 << i;

        for (uint8_t j = 0; j < 4; j++)
        {
            if (*self->_idr & (1 << j))
            {
                *self->_odr = 0;
                return (*self->map)[i][j]; // TODO: fix j-offset
            }
        }
    }

    *self->_odr = 0;

    return KEYPAD_NULL_KEY;
}

#endif /* KEYPAD_H */
