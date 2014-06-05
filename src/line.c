#include <stdlib.h>
#include <iso646.h>
#include <windows.h>
#include <stdio.h>

#include "line.h"

struct Line *Line_create() {
    struct Line * line = (struct Line *) malloc(sizeof(struct Line));
    if (line == NULL) {
        perror("Line_create malloc failed\n");
        exit(1);
    }

    line->index = 0;
    line->string = NULL;
    line->next = NULL;

    return line;
}

void Line_set_text(struct Line *line, char const *buf) {
    if (line == NULL)
        return;

    String_destory(line->string);
    line->string = String_create(buf);
}

struct Line *Line_create_with_text(char const *buf) {
    struct Line *line = Line_create();
    Line_set_text(line, buf);

    return line;
}

void Line_delete(struct Line *line) {
    String_destory(line->string);
    free(line);
}
