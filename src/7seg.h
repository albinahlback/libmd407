/* 7seg.h: Seven segmented display

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

#ifndef SEVENSEG_H
#define SEVENSEG_H

#include "gpio.h"

#define ISALPHA(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))

static const uint8_t seg_codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
                                    0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C,
                                    0x39, 0x5E, 0x79, 0x71};

typedef struct
{
    PGPIO port;
    char c;
}
SEVENSEG;

/* Function to connect 7 seg display to port */
void sevenseg_connect(SEVENSEG *self, PGPIO port)
{
	self->port = port;

	/* pin 7-0 outport, pin 15-8 inport */
	port->moder = 0x55005555;

	/* GPIO OT */
	port->otyper = 0x00FF;

	/* GPIO PUPDR */
	port->pupdr_high = 0x00AA;
}

/* Function to convert char to 7seg char */
int _sevenseg_get_char_index(char c)
{
	if (ISALPHA(c))
		return c - 'A' + 10;

	return c - '0';
}

/* Function to write to display */
void sevenseg_write(SEVENSEG *self, char c)
{
	self->c = c;
	int index = _sevenseg_get_char_index(self->c);

	if (index >= 16)
		self->port->odr_low = 0x0;
	else
		self->port->odr_low = seg_codes[index];
}

#endif /* SEVENSEG_H */
