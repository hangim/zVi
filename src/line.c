#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

void Line_set_index(struct Line * const line, const int index) {
    if (line == NULL)
        return;
    line->index = index;
}

void Line_set_text(struct Line * const line, const char *buf) {
    if (line == NULL)
        return;

    String_destory(line->string);
    line->string = String_create(buf);
}

struct Line *Line_create_with_text(const char *buf) {
    struct Line *line = Line_create();
    Line_set_text(line, buf);

    return line;
}

void Line_print(const struct Line * const line) {
    if (line == NULL)
        return;

    printf("%4d ", line->index);
    if (line->string == NULL)
        printf("\n");
    else
        String_print(line->string);
}

void Line_write(const struct Line * const line, FILE * const fp) {
    if (line == NULL or fp == NULL)
        return;

    String_write(line->string, fp);
}

void Line_destory(struct Line * const line) {
    String_destory(line->string);
    free(line);
}
