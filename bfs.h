#ifndef _BFS_H_
#define _BFS_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "color.h"
#include "array.h"

#define max(x, y) (x) > (y) ? (x) : (y)

struct pos2 {
    int x;
    int y;
};

struct bfs_node {
    struct pos2 p;
    int depth;
    struct bfs_node *next;
};

struct bfs_result {
    int step;
    int depth;
    int opened;
};

int **bfs_gen(int w, int h);
int **bfs_clone(int w, int h, int **bfs);
struct bfs_result bfs4_step(int x, int y, int w, int h, int **origin);
int bfs(int x, int y, int w, int h, int **map);
int bfs_test();

#endif //_BFS_H_