#include <stdio.h>

#include "line.h"

int main() {

    struct Line *line1 = Line_create_with_text("hello world\n");
    struct Line *line2 = Line_create_with_text("code is poetry\n");

    Line_set_index(line1, 1);
    Line_set_index(line2, 2);

    Line_print(line1);
    Line_print(line2);

    FILE *fp = fopen("line_test.out", "w");
    Line_write(line1, fp);
    Line_write(line2, fp);

    Line_destory(line1);
    Line_destory(line2);

    return 0;
}
