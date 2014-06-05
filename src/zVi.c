#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "view.h"

int main(int argc, char const *argv[]) {

    if (argc != 3)
        return -1; // TODO

    FILE *f_from = fopen(argv[1], "r");
    FILE *f_to = fopen(argv[2], "w");

    // TODO

    if (f_from)
        fclose(f_from);
    if (f_to)
        fclose(f_to);

    return 0;
}
