#include <stdio.h>
#include <iso646.h>

#include "view.h"

int main() {
    struct View *view;
    view = View_create();

    FILE *f = fopen("view_test.c", "r");

    View_read(view, f);
    View_print(view);

    printf("\n---\n");
    View_delete_in_range(view, 9, 13);
    View_print(view);

    View_destory(view);
    return 0;
}
