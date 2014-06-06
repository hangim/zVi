/******************************************************************************
 *
 * Filename:
 *  view_test.c
 *
 * Description:
 *   视图测试
 *
 ******************************************************************************/

#include <stdio.h>
#include <iso646.h>

#include "view.h"

int main() {


    FILE *fp_from = fopen("view_test.c", "r");
    FILE *fp_to = fopen("view_test.out", "w");

    struct View *view;
    view = View_create(fp_from, fp_to);

    View_read(view);
    View_print(view);
    View_write(view);
    View_clear(view);

    printf("\n---\n");
    View_read(view);
    View_print(view);
    
    printf("\n---\n");
    // View_delete_in_range(view, 1, 5);
    View_print(view);

    printf("\n---\n");

    View_destory(view);
    return 0;
}
