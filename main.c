#include <stdio.h>
#include <getopt.h>

#include "bfs.h"

static const struct option long_options[] = {
    {"help", no_argument, NULL, 'h'},
    {"bfs", no_argument, NULL, 'b'},
};

static void
help_print()
{
}

int
main(int argc, char **argv)
{
    int option_index = 0;
    int c = getopt_long(argc, argv, "hb", long_options, &option_index);
    if (c == -1) {
        return -1;
    }

    switch (c) {
    case 'h':
        help_print();
        break;
    case 'b':
        bfs_test();
        break;
    }

    return 0;
}