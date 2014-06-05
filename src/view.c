#include <stdlib.h>
#include <stdio.h>
#include <iso646.h>

#include "view.h"

struct View *View_create() {
    struct View *view = (struct View *) malloc(sizeof(struct View));
    if (view == NULL) {
        perror("View_create malloc failed\n");
        exit(1);
    }

    view->head = Line_create();
    view->size = 0;

    return view;
}

struct Line *View_get_line_by_index(struct View *view, int pos) {
    if (view == NULL)
        return NULL;

    if (pos < 0 or pos > view->size)
        return NULL;

    struct Line *line = view->head;

    if (pos == 0)
        return line;

    while (line->next->index != pos)
        line = line->next;

    return line->next;
}

void View_insert(struct View *view, struct Line *line, int pos) {
    if (view == NULL or line == NULL)
        return;

    struct Line *p = View_get_line_by_index(view, pos);
    if (p == NULL)
        return;

    struct Line *tmp = p->next;
    p->next = line;
    line->next = tmp;
    view->size++;
    
    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }
}

void View_insert_with_text(struct View *view, char const *buf, int pos) {
    if (view == NULL)
        return;
    struct Line *line = Line_create_with_text(buf);
    View_insert(view, line, pos);
}

void View_delete_by_index(struct View *view, int pos) {
    if (view == NULL or pos <= 0 or pos > view->size)
        return;

    struct Line *p = View_get_line_by_index(view, pos - 1);
    struct Line *tmp = p->next;
    p->next = tmp->next;
    Line_destory(tmp);

    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }
}

void View_delete_in_range(struct View *view, int from, int end) {
    if (view == NULL or from <= 0 or end > view->size or from > end)
        return;

    struct Line *p = View_get_line_by_index(view, from - 1);
    struct Line *tmp;
    while (p->next and (p->next->index >= from and p->next->index <= end)) {
        tmp = p->next;
        p->next = tmp->next;
        Line_destory(tmp);
    }

    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }
}

void View_print(struct View *view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;
    if (line == NULL)
        return;

    while (line->next) {
        Line_print(line->next);
        line = line->next;
    }
}

void View_destory(struct View *view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;
    if (line != NULL) {
        while (line) {
            struct Line *tmp = line;
            line = line->next;
            Line_destory(tmp);
        }
    }

    free(view);
}