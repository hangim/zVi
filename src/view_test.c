#include <stdio.h>
#include <iso646.h>

#include "view.h"

int main() {
    struct View *view;
    view = View_create();

    FILE *f_from = fopen("view_test.c", "r");
    FILE *f_to = fopen("view_test.out", "w");

    View_read(view, f_from);
    View_print(view);
    View_write(view, f_to);
    View_clear(view);

    printf("\n---\n");
    View_read(view, f_from);
    View_print(view);
    
    printf("\n---\n");
    View_delete_in_range(view, 1, 5);
    View_print(view);

    printf("\n---\n");

    View_destory(view);
    return 0;
}
