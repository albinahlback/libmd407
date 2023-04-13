/* t-gfx.c

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

#include "display.h"
#include "gfx.h"
#include "time.h"
#include "startup.h"

STARTUP_NOCRT;

int main()
{
    display_connect();
    /* delay_nano(1000000000); */

    line ln = LINE(POINT(0, 0), POINT(40, 40));
    vertex poly_verts[] = {POINT(0, 0), POINT(10, 0), POINT(10, 10), POINT(0, 10)};
    polygon poly = POLYGON(poly_verts, 4);
    rectangle rect = RECTANGLE(20, 10);
    sprite spr = SPRITE(12, 4, 4, PIXEL_ARRAY({{0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 1}, {3, 2}}));

    while (true)
    {
        display_clear();
        ln.pos = POINT(20, 0);
        ln.render(&ln);
        delay_milli(2000);

        display_clear();
        poly.pos = POINT(20, 40);
        poly.render(&poly);
        delay_milli(2000);

        display_clear();
        rect.pos = POINT(80, 40);
        rect.render(&rect);
        delay_milli(2000);

        display_clear();
        spr.pos = POINT(80, 40);
        spr.render(&spr, true);
        delay_milli(2000);
    }

    return 0;
}
