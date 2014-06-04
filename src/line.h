#ifndef zVi_LINE
#define zVi_LINE

#include "string.h"

struct Line_node {
    int index;
    struct String *string;
    struct Line_node *next;
};

struct Line {
    struct Line_node *head;
    int size;
};

struct Line_node * Line_create_node();
void Line_set_string(struct Line_node *node, char const *buf);
struct Line * Line_create();
struct Line_node * Line_get_node_by_index(struct Line *line, int pos);
void Line_insert(struct Line *line, struct Line_node *node, int pos);
void Line_delete(struct Line *line, int pos);

#endif
