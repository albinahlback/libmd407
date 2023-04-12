/* math.h

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

#ifndef MATH_H
#define MATH_H

#include "types.h"

#define PI 3.141592653589793
#define E 2.718281828459045

#define DEG_TO_RAD(deg) (deg * 0.017453292519943295)
#define RAD_TO_DEG(rad) (rad * 57.29577951308232)

#define ABS(x) (((x) <= 0) ? -(x) : (x))

#endif /* MATH_H */
