#include "color.h"

void set_color(int c)
{
    printf("\033[0;%dm", c);
}