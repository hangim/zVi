#include <stdio.h>

#include "line.h"

/*
struct Line *Line_create();
void Line_set_text(struct Line *line, char const *buf);
struct Line *Line_create_with_text(char const *buf);
void Line_delete(struct Line *line);
*/

int main() {

    struct Line *line = Line_create();

    printf("%d\n", line->index);

    Line_delete(line);

    return 0;
}