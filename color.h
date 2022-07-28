#ifndef _COLOR_H_
#define _COLOR_H_
#include <stdio.h>

enum {
    CLR = 0,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    PURPLE = 35,
    CYAN = 36,
    WHITE = 37,
};

void set_color(int c);

#endif //_COLOR_H_