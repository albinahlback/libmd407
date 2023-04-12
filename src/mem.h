/* mem.h

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

#ifndef MEM_H
#define MEM_H

#define BIT(type, addr, oper, mask) (*((type *) addr) oper mask)

#define BIT_SET(type, addr, mask)    BIT(type, addr, |=, mask)
#define BIT_CLEAR(type, addr, mask)  BIT(type, addr, &= ~, mask)
#define BIT_TOGGLE(type, addr, mask) BIT(type, addr, ^=, mask)

#define BIT_CHECK(type, addr, mask)         BIT(type, addr, &, mask)
#define BIT_CHECK_ALL(type, addr, mask)     (BIT_CHECK(type, addr, mask) == mask)
#define BIT_CHECK_ANY(type, addr, mask)     (BIT_CHECK(type, addr, mask) != 0)
#define BIT_CHECK_NONE(type, addr, mask)    (BIT_CHECK(type, addr, mask) == 0)
#define BIT_CHECK_EXACT(type, addr, mask)   (BIT_CHECK(type, addr, mask) == mask)
#define BIT_CHECK_NOT(type, addr, mask)     (BIT_CHECK(type, addr, mask) != mask)

/* 32bit data table */
#define DT_32(name)             \
union                           \
{                               \
    uint32_t name;              \
    struct                      \
    {                           \
        uint16_t name##_low;    \
        uint16_t name##_high;   \
    };                          \
    struct                      \
    {                           \
        uint8_t name##_0;       \
        uint8_t name##_1;       \
        uint8_t name##_2;       \
        uint8_t name##_3;       \
    };                          \
}

/* 16 bit data table to the right */
#define DT_16_R(name)                   \
union                                   \
{                                       \
    struct                              \
    {                                   \
        uint16_t name;                  \
        uint16_t _RESERVED_##name##_0;  \
    };                                  \
    struct                              \
    {                                   \
        uint8_t name##_low;             \
        uint8_t name##_high;            \
        uint16_t _RESERVED_##name##_1;  \
    };                                  \
}

/* 16 bit data table to the left */
#define DT_16_L(name)                   \
union                                   \
{                                       \
    struct                              \
    {                                   \
        uint16_t _RESERVED_##name##_0;  \
        uint16_t name;                  \
    };                                  \
    struct                              \
    {                                   \
        uint16_t _RESERVED_##name##_1;  \
        uint8_t name##_low;             \
        uint8_t name##_high;            \
    };                                  \
}

#endif /* MEM_H */
