/* crt.h: C run time

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

#ifndef CRT_H
#define CRT_H

void crt_init(void)
{
    extern char __bss_start;
    extern char __bss_end;
    extern char __heap_low;
    extern char __heap_top;
    char * s;

    s = &__bss_start;
    while (s < &__bss_end)
        *s++ = 0;

    s = &__heap_low;
    while (s < &__heap_top)
        *s++ = 0;
}

void crt_deinit(void) { }

#if 0
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

static char * heap_end;

#define MAX_FILENO 5
#define KEYPAD_FILENO 3
#define ASCII_DISPLAY_FILENO 4

typedef struct
{
    char name[16];
    int (*init) (int);
    void (*deinit) (int);
    int (*fstat)(struct stat *st);
    int (*isatty)(void);
    int (*open)(const char name,int flags,int mode);
    int (*close)(void);
    int (*lseek)(int ptr, int dir);
    int (*write)(char *ptr, int len);
    int (*read)(char *ptr, int len);
}
DEV_DRIVER_DESC, * PDEV_DRIVER_DESC;

static DEV_DRIVER_DESC keypad =
{
    "Keypad",
    keypad_init,
    keypad_deinit,
    0,
    0,
    0,
    0,
    0,
    0,
    keypad_read
};

PDEV_DRIVER_DESC device_table[MAX_FILENO] =
{
    &stdin,
    &stdout,
    &stderr,
    &keypad,
    &asciidisplay,
};

int _close(int file)
{
    return -1;
}

int _fstat(int file, struct stat * st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _open(const char *name, int flags, int mode)
{
    return -1;
}

int _read(int file, char *ptr, int len)
{
    PDEV_DRIVER_DESC drvr;
    drvr = device_table[file];
    if (drvr == 0)
        return 0;
    return drvr->read(ptr,len);
}

int _write(int file, char *ptr, int len)
{
    PDEV_DRIVER_DESC drvr;
    drvr = device_table[file];
    if (drvr == 0)
        return 0;
    return drvr->write(ptr,len);
}
#endif

#endif /* CRT_H */
