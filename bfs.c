#include "bfs.h"

struct pos2 dir4[4] = {
    {-1, 0}, // left
    {1, 0},  // right
    {0, -1}, // down
    {0, 1},  // up
};

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

static struct bfs_node *
create_node(int x, int y, int depth)
{
    struct bfs_node *n = (struct bfs_node *)malloc(sizeof(struct bfs_node));
    n->p.x = x;
    n->p.y = y;
    n->depth = depth;
    return n;
}

int **
bfs_gen(int w, int h)
{
    int **map = (int **)malloc(sizeof(int *) * h);
    for (int y = 0; y < h; y++) {
        map[y] = (int *)malloc(sizeof(int *) * w);
        for (int x = 0; x < w; x++) {
            int v = X;
            if (rand() % 2) {
                v = O;
            }
            map[y][x] = v;
        }
    }

    return map;
}

int **
bfs_clone(int w, int h, int **bfs)
{
    int **map = (int **)malloc(sizeof(int *) * h);
    for (int y = 0; y < h; y++) {
        map[y] = (int *)malloc(sizeof(int *) * w);
        for (int x = 0; x < w; x++) {
            map[y][x] = bfs[y][x];
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

struct bfs_result
bfs4_step(int x, int y, int w, int h, int **origin)
{
    int **map = bfs_clone(w, h, origin);

    set_map(map, x, y, S);
    array_2d_print(w, h, map);
    int step = 1;
    int depth = 0;
    int opened = 0;

    struct bfs_node *n = create_node(x, y, depth);
    struct bfs_node *tail = n;
    struct bfs_node *head = n;

    while (head != NULL) {
        getchar();
        struct bfs_node *cur = head;

        printf("step %d, depth=%d\n", step, cur->depth);
        depth = max(cur->depth, depth);
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
            struct bfs_node *new_node = create_node(xx, yy, cur->depth + 1);
            new_node->next = NULL;
            tail->next = new_node;
            tail = new_node;

            step++;
        }

        head = cur->next;
        free(cur);

        array_2d_print(w, h, map);
    }

    bfs_free(w, h, map);
    struct bfs_result result = {step, depth, opened};
    return result;
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
    array_2d_print(w, h, map);
    bfs_free(w, h, map);

    w = 11;
    h = 10;
    map = bfs_gen(w, h);
    array_2d_print(w, h, map);
    bfs_free(w, h, map);

    w = 10;
    h = 11;
    map = bfs_gen(w, h);
    array_2d_print(w, h, map);
    bfs_free(w, h, map);

    w = 11;
    h = 11;
    map = bfs_gen(w, h);
    array_2d_print(w, h, map);
    bfs_free(w, h, map);

    printf("====================================\n\n");

    printf("test map\n");
    map = bfs_gen(w, h);
    array_2d_print(w, h, map);

    struct bfs_result result = bfs4_step(rand() % w, rand() % h, w, h, map);

    printf("step: %d, depth: %d, opened: %d\n", result.step, result.depth, result.opened);

    bfs_free(w, h, map);

    return 0;
}