/* exceptions.h

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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "types.h"

/*
// PS register control
__attribute__((naked)) uint32_t _get_psr_reg() {
	__asm__ volatile("MRS R0, PSR\n");
	__asm__ volatile("BX LR\n");
}

__attribute__((naked)) void _set_psr_reg(uint32_t apsr) {
	__asm__ volatile("MSR PSR_nvzcq\n");
	__asm__ volatile("BX LR\n");
}

// Control register control
__attribute__((naked)) uint32_t _get_ctrl_reg() {
	__asm__ volatile("MRS R0, CONTROL\n");
	__asm__ volatile("BX LR\n");
}

__attribute__((naked)) void _set_ctrl_reg(uint32_t x) {
	__asm__ volatile("MSR CONTROL, R0\n");
	__asm__ volatile("BX LR\n");
}

// Enable/disable interrupts
__attribute__((naked)) void _int_enable() {
	__asm__ volatile("CPSIE I\n");
	__asm__ volatile("BX LR\n");
}
__attribute__((naked)) void _int_disable() {
	__asm__ volatile("CPSID I\n");
	__asm__ volatile("BX LR\n");
}
*/

#define EXCEPTION_ASSIGN(offset, func)                  \
do                                                      \
{                                                       \
    *((void (**)(void))(0x2001C000 + offset)) = &func;  \
}                                                       \
while (0)

#endif /* EXCEPTIONS_H */
