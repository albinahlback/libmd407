/* gpio.h

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

#ifndef GPIO_H
#define GPIO_H

#include "mem.h"
#include "types.h"

typedef struct
{
    DT_32(moder); /* Port mode Register */
    DT_16_R(otyper); /* Output TYPE Register */
    DT_32(ospeedr); /* Output SPEED Register */
    DT_32(pupdr); /* Pull-up/Pull-down Register */
    DT_16_R(idr); /* Input data Register */
    DT_16_R(odr); /* Output data Register */
    uint32_t bsrr; /* Bit set/reset Register */
    uint32_t lckr; /* Configuration Lock Register */
    uint32_t afrl; /* Alternate function low Register */
    uint32_t afrh; /* Alternate function high Register */
}
GPIO, * PGPIO;

#define GPIO_A ((PGPIO) 0x40020000)
#define GPIO_B ((PGPIO) 0x40020400)
#define GPIO_C ((PGPIO) 0x40020800)
#define GPIO_D ((PGPIO) 0x40020C00)
#define GPIO_E ((PGPIO) 0x40021000)

#endif /* GPIO_H */
