/* debug.h: Debugging header

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

#ifndef DEBUG_H
#define DEBUG_H

#include "types.h"

#define _USART_BASE (0x40011000)
#define USART(n) ((PUSART) _USART_BASE + 0x1400 * (n))

typedef volatile struct __attribute__((packed))
{
	uint16_t sr;
	uint16_t Unused0;
	uint16_t dr;
	uint16_t Unused1;
	uint16_t brr;
	uint16_t Unused2;
	uint16_t cr1;
	uint16_t Unused3;
	uint16_t cr2;
	uint16_t Unused4;
	uint16_t cr3;
	uint16_t Unused5;
	uint16_t gtpr;
}
USART, * PUSART;

static void print_char(char c, unsigned char id)
{
	while ((USART(id)->sr & 0x80) == 0) ;
	USART(id)->dr = (uint16_t) c;
	if (c == '\n')
		print_char('\r', id);
}

void print_usart(const char * s, unsigned char id)
{
	while (*s)
		print_char(*s++, id);
}

void printc(const char * s)
{
	print_usart(s, 0);
}

#endif /* DEBUG_H */
