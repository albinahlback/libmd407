/* lcd.h

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

#ifndef LCD_H
#define LCD_H

#include "gpio.h"
#include "mem.h"
#include "time.h"
#include "types.h"

#define _LCD_CMD_RS     1
#define _LCD_CMD_RW     2
#define _LCD_CMD_SELECT 4
#define _LCD_CMD_ENABLE 0x40

#define _LCD_NL '\n'
#define _LCD_CR '\r'

#define _LCD_WAIT_STATE_FLAG while ((_lcd_read_status(self) & 0x80) == 0x80)

/* FIXME: might be broken */
#define _LCD_CTRL_BIT_SET(mask)                                     \
    BIT_SET(uint8_t, &self->port->odr_low, mask | _LCD_CMD_SELECT)

#define _LCD_CTRL_BIT_CLEAR(mask)                                   \
    BIT_CLEAR(uint8_t, &self->port->odr_low, mask | _LCD_CMD_SELECT)

typedef struct
{
    PGPIO port;
}
lcd;

/* Read from display controller */
uint8_t _lcd_read_ctrl(lcd * self)
{
    uint8_t rv;
    _LCD_CTRL_BIT_SET(_LCD_CMD_ENABLE);

    delay_nano(360);

    rv = self->port->idr_high;

    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_ENABLE);

    return rv;
}

/* Read status of the display */
uint8_t _lcd_read_status(lcd * self)
{
    uint8_t ret;

    self->port->moder &= 0x0000FFFF;

    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS);
    _LCD_CTRL_BIT_SET(_LCD_CMD_RW);

    ret = _lcd_read_ctrl(self);

    self->port->moder |= 0x55550000;

    return ret;
}

/* Write to display controller */
void _lcd_write_ctrl(lcd * self, uint8_t cmd)
{
    /* Enable control bit */
    _LCD_CTRL_BIT_SET(_LCD_CMD_ENABLE);

    /* Write command */
    self->port->odr_high = cmd;

    /* Wait and disable */
    delay_250ns(); /* NOTE: should be 230 but 250 is more safe */
    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_ENABLE);
}

/* Write a command to the display */
void _lcd_write_cmd(lcd * self, uint8_t cmd)
{
    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS | _LCD_CMD_RW);
    _lcd_write_ctrl(self, cmd);
}

void lcd_clear(lcd * self)
{
    /* Clear the screen */
    _LCD_WAIT_STATE_FLAG;
    delay_micro(8);
    _lcd_write_cmd(self, 1);
    delay_milli(2);

    /* Return home */
    _LCD_WAIT_STATE_FLAG;
    delay_micro(8);
    _lcd_write_cmd(self, 2);
    delay_milli(2);
}

void lcd_connect(lcd * self, PGPIO port)
{
    /* Start the clock for the GPIO D & E ports */
    self->port = port;

    /* Set port state */
    self->port->moder = 0x00005555;

    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_RW);
    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS);

    /* Display control */
    _LCD_WAIT_STATE_FLAG;
    delay_micro(8);
    _lcd_write_cmd(self, 0b00001111);
    delay_micro(40);

    /* Function set */
    _LCD_WAIT_STATE_FLAG;
    delay_micro(8);
    _lcd_write_cmd(self, 0b00111011);
    delay_micro(40);

    /* Clear screen & set cursor at 0, 0 */
    lcd_clear(self);

    /* Entry mode set */
    _LCD_WAIT_STATE_FLAG;
    delay_micro(8);
    _lcd_write_cmd(self, 0b00000110);
    delay_micro(40);
}

/* Write data to the data port */
void _lcd_write_data(lcd * self, uint8_t data)
{
    /* Set the controller to write mode */
    _LCD_CTRL_BIT_CLEAR(_LCD_CMD_RW);
    _LCD_CTRL_BIT_SET(_LCD_CMD_RS);

    /* Write data */
    _lcd_write_ctrl(self, data);
}

/* Read data from the display */
uint8_t _lcd_read_data(lcd * self)
{
    uint8_t ret;

    _LCD_CTRL_BIT_SET(_LCD_CMD_RW);
    _LCD_CTRL_BIT_SET(_LCD_CMD_RS);

    ret = _lcd_read_ctrl(self);

    return ret;
}

/* Write char to display */
void _lcd_write_char(lcd * self, uint8_t c)
{
    _LCD_WAIT_STATE_FLAG;
    _lcd_write_data(self, c);
    delay_micro(44); /* 43 */
}

void lcd_set_cursor(lcd * self, uint8_t x, uint8_t y)
{
    int offset = x;
    offset += 0x40 * y;

    _lcd_write_cmd(self, 0x80 | offset);
}

void lcd_puts(lcd * self, uint8_t x, uint8_t y, char * text)
{
    lcd_set_cursor(self, x, y);
    do
    {
        switch (*text)
        {
            case _LCD_NL:
                lcd_set_cursor(self, x, ++y);
                continue;
            case _LCD_CR:
                lcd_set_cursor(self, 0, y);
                continue;
            default:
                _lcd_write_char(self, *text);
                break;
        }
    } while (*text++);
}

#endif /* LCD_H */
