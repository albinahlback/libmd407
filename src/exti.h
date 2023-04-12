/* exti.h

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

#ifndef EXTI_H
#define EXTI_H

#include "mem.h"
#include "types.h"

#define _EXTI_REG(r)    \
union                   \
{                       \
    uint32_t _##r;      \
    unsigned r : 23;    \
}

typedef volatile struct
{
	_EXTI_REG(imr);
	_EXTI_REG(emr);
	_EXTI_REG(rtsr);
	_EXTI_REG(ftsr);
	_EXTI_REG(swier);
	_EXTI_REG(pr);
}
* PEXTI;

#define EXTI ((PEXTI) 0x40013C00)

#endif /* EXTI_H */
