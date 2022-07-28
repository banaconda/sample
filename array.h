#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdio.h>
#include <math.h>

#include "color.h"

enum {
    O = 'O', // empty
    X = 'X', // block
    C = 'C', // check
    S = 'S', // start
};

void array_2d_print(int w, int h, int **map);

#endif //_ARRAY_H_