#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "color.h"

enum {
    O, // empty
    X, // block
    C, // check
    S, // start
};

struct pos {
    int x;
    int y;
};

struct node {
    struct pos p;
    struct node *next;
};

struct pos dir4[4] = {
    {-1, 0}, // left
    {1, 0},  // right
    {0, -1}, // down
    {0, 1},  // up
};

void
bfs_print(int w, int h, int **map)
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
                putchar('O');
                break;
            case X:
                set_color(PURPLE);
                putchar('X');
                break;
            case C:
                set_color(RED);
                putchar('C');
                break;
            case S:
                set_color(YELLOW);
                putchar('S');
                break;
            }
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

int **
bfs_gen(int w, int h)
{
    int **map = (int **)malloc(sizeof(int *) * h);
    for (int y = 0; y < h; y++) {
        map[y] = (int *)malloc(sizeof(int *) * w);
        for (int x = 0; x < w; x++) {
            map[y][x] = rand() % 2;
        }
    }

    return map;
}

void
bfs_free(int w, int h, int **map)
{
    for (int y = 0; y < h; y++) {
        free(map[y]);
    }
    free(map);
}

static inline void
set_map(int **map, int x, int y, int value)
{
    map[y][x] = value;
}

static inline int
get_map(int **map, int x, int y)
{
    return map[y][x];
}

// closed return 1
// opened return 0
int
bfs4(int x, int y, int w, int h, int **map)
{
    set_map(map, x, y, S);
    bfs_print(w, h, map);
    int step = 1;
    int opened = 0;

    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->p.x = x;
    n->p.y = y;
    struct node *tail = n;
    struct node *head = n;

    while (head != NULL) {
        getchar();
        struct node *cur = head;

        printf("step %d\n", step);
        for (int i = 0; i < 4; i++) {
            int dx = dir4[i].x;
            int dy = dir4[i].y;
            int xx = cur->p.x + dx;
            int yy = cur->p.y + dy;

            if (xx < 0 || xx >= w || yy < 0 || yy >= h) {
                printf("exceed x: %d, y: %d, dx: %d, dy: %d\n", x, y, dx, dy);
                opened = 1;
                continue;
            }

            if (get_map(map, xx, yy) != O) {
                printf("conflict x: %d, y: %d, dx: %d, dy: %d\n", x, y, dx, dy);
                continue;
            }

            set_map(map, xx, yy, C);
            struct node *new_node = (struct node *)malloc(sizeof(struct node));
            new_node->p.x = xx;
            new_node->p.y = yy;
            new_node->next = NULL;
            tail->next = new_node;
            tail = new_node;

            step++;
        }

        head = cur->next;
        free(cur);

        bfs_print(w, h, map);
    }

    return opened;
}

int
bfs_test()
{
    srand((unsigned)time(NULL));
    int w = 10;
    int h = 10;
    int **map;

    w = 10;
    h = 10;
    map = bfs_gen(w, h);
    bfs_print(w, h, map);
    bfs_free(w, h, map);

    w = 11;
    h = 10;
    map = bfs_gen(w, h);
    bfs_print(w, h, map);
    bfs_free(w, h, map);

    w = 10;
    h = 11;
    map = bfs_gen(w, h);
    bfs_print(w, h, map);
    bfs_free(w, h, map);

    w = 11;
    h = 11;
    map = bfs_gen(w, h);
    bfs_print(w, h, map);
    bfs_free(w, h, map);

    printf("====================================\n\n");

    printf("test map\n");
    map = bfs_gen(w, h);
    bfs_print(w, h, map);

    int opened = bfs4(rand() % w, rand() % h, w, h, map);
    if (opened) {
        printf("opened\n");
    } else {
        printf("closed\n");
    }

    bfs_free(w, h, map);

    return 0;
}