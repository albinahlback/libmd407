# MD407 Utils Library

This library contains a collection of utilities and helpful functions, data
structures, macros, etc. for MD407 computers used at the Machine Oriented
Programming course at Chalmers University of Technology.


## Usage

Include the headers like: `#include <md407/debug.h>`, and link the desired stuff.

### Example
```c
#include <md407/gpio.h>
#include <md407/time.h>
#include <md407/debug.h>

int
main(void)
{
    /* Set pins 7-15 as outputs */
    GPIO_E->moder_high = 0x5555;

    /* Delay for 1 second */
    delay_milli(1000);

    /* Write 'E' to the output */
    GPIO_E->odr_high = 'E';

    /* Print a text to USART1 for debug */
    printc("Hello World!\n");

    return 0;
}
```


## Installation

This library only allows for Unix-type systems. It requires the following
programs, where `HOST` is typically is `arm-none-eabi`:

- `$HOST-gcc`, the C compiler for `HOST`,
- `$HOST-objcopy`, the objcopy for `HOST`,
- `$HOST-ar`, the archiver for `HOST`, and
- `autoreconf`.

On Arch-Linux, these can be installed through
```
pacman -S arm-none-eabi-gcc
pacman -S arm-none-eabi-newlib
pacman -S autoconf
```

The installation procedure that follows is then very typical of the installation
process of many GNU/Linux projects:
```
cd path/to/libmd407
./bootstrap.sh
./configure --host=$HOST --prefix=path/to/my/installation/path
make install
```

Although some users prefer installing it to `/usr/arm-none-eabi`, the author of
this fork recommends instead to install it under your `$HOME` to avoid the use
of any unnecessary root usage.


## Authors
- [Elias Almqvist](https://github.com/almqv)
- [Ismail Sacic](https://github.com/ismail424)
- Albin Ahlbäck


## License
This project is licensed under the GNU v2 License - see the [LICENSE](LICENSE) file for details
