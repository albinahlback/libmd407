/* display.h: Display header

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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "gpio.h"
#include "types.h"

__attribute__((naked))
void _display_init(void)
{
    asm volatile (".HWORD 0xDFF0\n"
                 "BX LR\n");
}

__attribute__((naked))
void display_clear(void)
{
    asm volatile (".HWORD 0xDFF1\n"
                  "BX LR\n");
}

__attribute__((naked))
void _display_px_set(int x, int y)
{
    asm volatile (".HWORD 0xDFF2\n"
                 "BX LR\n");
}

__attribute__((naked))
void _display_px_clear(int x, int y)
{
    asm volatile (".HWORD 0xDFF3\n"
                  "BX LR\n");
}

void display_connect(void)
{
	_display_init();
	display_clear();
}

void display_set_pixel(int x, int y, int set)
{
	/* x and y needs to be between 1 and 128, inclusive */
	x++;
	y++;
	if (set)
		_display_px_set(x, y);
	else
		_display_px_clear(x, y);
}

#endif /* DISPLAY_H */
