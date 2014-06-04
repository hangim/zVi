#include <stdlib.h>

#include "line.h"

struct Line_node * Line_create_node() {
    struct Line_node * node = (struct Line_node *) malloc(sizeof(struct Line_node));
    if (node == NULL)
        ; // TODO

    node->string = NULL;
    node->index = 0; // TODO
    node->next = NULL;

    return node;
}

void Line_set_string(struct Line_node *node, char const *buf) {
    if (node->string != NULL)
        String_destory(node->string);

    node->string = String_create(buf);
}

struct Line * Line_create() {
    struct Line *line = (struct Line *) malloc(sizeof(struct Line));
    if (line == NULL)
        ; // TODO

    line ->head = Line_create_node();
    if (line->head == NULL)
        ; // TODO

    line->size = 0;

    return line;
}

struct Line_node * Line_get_node_by_index(struct Line *line, int pos) {
    if (line == NULL)
        ; // TODO
    if (pos < 0 or pos > line->size)
        return NULL;

    struct Line_node *p = line->head;

    if (pos == 0)
        return p;

    while (p->next->index != pos)
        p = p->next;

    return p->next;
}

void Line_insert(struct Line *line, struct Line_node *node, int pos) {
    
    struct Line_node *p = Line_get_node_by_index(line, pos);
    if (p == NULL)
        ; // TODO

    struct Line_node *tmp = p->next;
    p->next = node;
    node->next = tmp;
    line->size++;
    
    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }
}

void Line_delete(struct Line *line, int pos) {
    struct Line_node *p, *q;

    p = Line_get_node_by_index(line, pos - 1);
    if (p == NULL)
        ; // TODO

    q = p->next;

    p->next = q->next;

    free(q); // TODO
    // TODO update index
}
