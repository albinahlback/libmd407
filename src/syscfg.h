/* syscfg.h

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

#ifndef SYSCFG_H
#define SYSCFG_H

#include "mem.h"
#include "types.h"

#define _SYSCFG_EXTI_DT_16_R(name)  \
    union {                         \
        uint32_t _##name;           \
        struct {                    \
            uint16_t name;          \
            unsigned : 16;          \
        };                          \
        struct {                    \
            unsigned name##_0 : 4;  \
            unsigned name##_1 : 4;  \
            unsigned name##_2 : 4;  \
            unsigned name##_3 : 4;  \
            unsigned          : 16; \
        };                          \
    }

typedef volatile struct
{
    /* MEMRMP */
    union
    {
        uint32_t memrmp;
        struct
        {
            unsigned memrmp_0 : 1;
            unsigned memrmp_1 : 1;
            unsigned memrmp_2 : 1;
            unsigned          : 5;
            unsigned memrmp_3 : 1;
            unsigned          : 1;
            unsigned memrmp_4 : 1;
            unsigned memrmp_5 : 1;
        };
    };

    /* PMC */
    union
    {
        uint32_t pmc;
        struct
        {
            unsigned         : 16;
            unsigned ADCxDC2 : 3;
            unsigned         : 4;
            unsigned R_SEL   : 1;
        };
    };

    /* EXTICR */
    _SYSCFG_EXTI_DT_16_R(exticr1);
    _SYSCFG_EXTI_DT_16_R(exticr2);
    _SYSCFG_EXTI_DT_16_R(exticr3);
    _SYSCFG_EXTI_DT_16_R(exticr4);

    /* CMPCR */
    union
    {
        uint32_t cmpcr;
        struct
        {
            unsigned cmpcr_0 : 1;
            unsigned         : 7;
            unsigned cmpcr_1 : 1;
        };
    };
}
* PSYSCFG;

#define SYSCFG ((PSYSCFG) 0x40013800)

#endif /* SYSCFG_H */
