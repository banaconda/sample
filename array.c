#include "array.h"

void
array_2d_print(int w, int h, int **map)
{
    putchar('\n');
    int y_pad = (int)log10(h - 1) + 1;
    int x_pad = (int)log10(w - 1) + 1;
    for (int y = h - 1; y >= 0; y--) {
        printf("%*d", y_pad, y);
        for (int x = 0; x < w; x++) {
            printf("%*s", x_pad, "");
            switch (map[y][x]) {
            case O:
                set_color(GREEN);
                break;
            case X:
                set_color(PURPLE);
                break;
            case C:
                set_color(RED);
                break;
            case S:
                set_color(YELLOW);
                break;
            }
            putchar((char)map[y][x]);
            set_color(CLR);
        }
        putchar('\n');
    }

    printf("%*s", y_pad, "");
    for (int x = 0; x < w; x++) {
        printf("%*d", x_pad + 1, x);
    }
    putchar('\n');
    putchar('\n');
}
