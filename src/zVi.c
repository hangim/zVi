#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "zVi.h"

int main(int argc, char const *argv[]) {

    if (argc != 3)
        return -1; // TODO

    FILE *f_from = fopen(argv[1], "r");
    FILE *f_to = fopen(argv[2], "w");

    struct View *view = View_create();

    // TODO command
    View_read(view, f_from);
    View_print(view);

    char buf[COMMAND_SIZE + 1];
    while (scanf("%s", buf)) {
        // printf("%c\n", buf[0]);
        if (buf[0] == 'i') {
            continue;
        }
        if (buf[0] == 'd') {
            continue;
        }
        if (buf[0] == 'n') {
            View_write(view, f_to);
            View_clear(view);
            View_read(view, f_from);
            View_print(view);
            continue;
        }
        if (buf[0] == 'p') {
            View_print(view);
            continue;
        }
        if (buf[0] == 'q') {
            View_write(view, f_to);
            View_destory(view);
            break;
        }
    }

    if (f_from)
        fclose(f_from);
    if (f_to)
        fclose(f_to);

    return 0;
}
