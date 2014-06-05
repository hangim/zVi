#ifndef zVi_LINE
#define zVi_LINE

#include "string.h"

struct Line {
    int index;
    struct String *string;
    struct Line *next;
};

struct Line *Line_create();
void Line_set_text(struct Line *line, char const *buf);
struct Line *Line_create_with_text(char const *buf);
void Line_destory(struct Line *line);
void Line_print(struct Line *line);
void Line_set_index(struct Line *line, int index);

#endif
