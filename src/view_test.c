#include <stdio.h>

#include "view.h"

int main() {
    struct View *view;
    view = View_create();

    View_insert_with_text(view, "hello\n", 0);
    View_insert_with_text(view, "world\n", 1);
    View_insert_with_text(view, "test\n", 1);
    View_print(view);

    printf("---\n");
    
    View_delete_in_range(view, 1, 2);
    View_print(view);

    View_destory(view);
    return 0;
}
