/* gfx.h: Rendering graphics

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

#ifndef GFX_H
#define GFX_H

#include "display.h"
#include "math.h"
#include "types.h"
#include "util.h"

#define _GFX_SPRITE_MAX_PIXELS 30

typedef struct
{
    char x;
    char y;
}
vertex, point;

typedef struct line
{
    vertex vert1;
    vertex vert2;
    point pos;
    void (* render)(struct line * self);
}
line;

typedef struct polygon
{
    vertex * verts;
    size_t count;
    point pos;
    void (* render)(struct polygon * self);
}
polygon;

typedef struct rectangle
{
    uint8_t width;
    uint8_t height;
    point pos;
    void (* render)(struct rectangle * self);
}
rectangle;

typedef struct sprite
{
    uint8_t width;
    uint8_t height;
    point pos;
    void (* render)(struct sprite * self, boolean on);
    uint8_t count;
    point pixels[_GFX_SPRITE_MAX_PIXELS];
}
sprite;

#define POINT(xx, yy) ((point) { .x = xx, .y = yy })

#define LINE(v1, v2)                \
    ((line) {                       \
        .vert1 = v1,                \
        .vert2 = v2,                \
        .pos = POINT(0, 0),         \
        .render = &_gfx_line_render \
    })

#define POLYGON(vs, cc)                                 \
    ((polygon) {                                        \
        .verts = vs, .count = cc, .pos = POINT(0, 0),   \
        .render = &_gfx_polygon_render                  \
    })

#define RECTANGLE(w, h)                                 \
    ((rectangle) {                                      \
        .width = w, .height = h, .pos = POINT(0, 0),    \
        .render = &_gfx_rectangle_render                \
    })

#define SQUARE(w) RECTANGLE(w, w)

#define PIXEL_ARRAY(...)       __VA_ARGS__

#define SPRITE(nm, w, h, pxs)               \
    ((sprite) {                             \
        .width = w, .height = h,            \
        .pos = POINT(0, 0), .count = nm,    \
        .render = &_gfx_sprite_render,      \
        .pixels = pxs                       \
    })

void _gfx_line_render(line * self)
{
    char x0 = self->vert1.x + self->pos.x;
    char x1 = self->vert2.x + self->pos.x;
    char y0 = self->vert1.y + self->pos.y;
    char y1 = self->vert2.y + self->pos.y;
    boolean steep = (ABS(y1 - y0) > ABS(x1 - x0));
    int delta_x, delta_y;
    int y, ystep;
    int ix;
    int error;

    if (steep)
    {
        SWAP(char, &x0, &y0);
        SWAP(char, &x1, &y1);
    }

    if (x0 > x1)
    {
        SWAP(char, &x0, &x1);
        SWAP(char, &y0, &y1);
    }

    delta_x = x1 - x0;
    delta_y = ABS(y1 - y0);

    error = 0;
    y = y0;
    ystep = y0 < y1 ? 1 : -1;

    for (ix = x0; ix <= x1; ix++)
    {
        if (steep)
            display_set_pixel(y, ix, true);
        else
            display_set_pixel(ix, y, true);

        error += delta_y;
        if ((error << 1) >= delta_x)
        {
            y += ystep;
            error -= delta_x;
        }
    }
}

void _gfx_polygon_render(polygon * self)
{
    line line_buf;

    /* Draw each line from i -> i+1 */
    for (int i = 0; i < (self->count - 1); i++)
    {
        line_buf = LINE(self->verts[i], self->verts[i + 1]);
        line_buf.pos = self->pos;
        _gfx_line_render(&line_buf);
    }

    /* Draw the line from the last vertex to the first */
    line_buf = LINE(self->verts[self->count - 1], self->verts[0]);
    line_buf.pos = self->pos;
    _gfx_line_render(&line_buf);
}

void _gfx_rectangle_render(rectangle * self)
{
    uint8_t dx, dy;

    /* Render the sides */
    for (dy = 0; dy <= self->height; dy++)
    {
        display_set_pixel(self->pos.x, self->pos.y + dy, true);
        display_set_pixel(self->pos.x + self->width, self->pos.y + dy, true);
    }

    /* Render the bottom and top lines */
    for (dx = 0; dx <= self->width; dx++)
    {
        display_set_pixel(self->pos.x + dx, self->pos.y, true);
        display_set_pixel(self->pos.x + dx, self->pos.y + self->height, true);
    }
}

void _gfx_sprite_render(sprite * self, boolean on)
{
    point pxBuf;
    int ix;

    for (ix = 0; ix < self->count; ix++)
    {
        pxBuf = self->pixels[ix];
        display_set_pixel(pxBuf.x + self->pos.x, pxBuf.y + self->pos.y, on);
    }
}

#endif /* GFX_H */
