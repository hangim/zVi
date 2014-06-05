#include <stdlib.h>
#include <stdio.h>
#include <iso646.h>
#include <windows.h>

#include "view.h"

/*
void test(struct View *view) {
    printf("\t\t%dhead \n", view->head->index);
    printf("\t\t%dtail \n", view->tail->index);
    printf("\t\t%dcount \n", view->count);
}
*/

struct View *View_create() {
    struct View *view = (struct View *) malloc(sizeof(struct View));
    if (view == NULL) {
        perror("View_create malloc failed\n");
        exit(1);
    }

    view->head = view->tail = Line_create();
    view->size = 0;
    view->count = 0;

    return view;
}

struct Line *View_get_line_by_index(struct View *view, int pos) {
    if (view == NULL)
        return NULL;

    if (pos < view->head->index or pos > view->tail->index)
        return NULL;

    struct Line *line = view->head;

    if (pos == line->index)
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

    view->tail = p;

    view->count = view->tail->index;
}

void View_insert_with_text(struct View *view, char const *buf, int pos) {
    if (view == NULL)
        return;
    struct Line *line = Line_create_with_text(buf);
    View_insert(view, line, pos);
}

void View_delete_by_index(struct View *view, int pos) {
    if (view == NULL or pos <= view->head->index or pos > view->tail->index)
        return;

    struct Line *p = View_get_line_by_index(view, pos - 1);
    struct Line *tmp = p->next;
    p->next = tmp->next;
    Line_destory(tmp);
    view->size--;

    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }

    view->tail = p;
    
    view->count = view->tail->index;
}

void View_delete_in_range(struct View *view, int from, int end) {
    if (view == NULL or from > end)
        return;

    struct Line *p = View_get_line_by_index(view, from - 1);
    struct Line *tmp;
    while (p->next and (p->next->index >= from and p->next->index <= end)) {
        tmp = p->next;
        p->next = tmp->next;
        Line_destory(tmp);
        view->size--;
    }

    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }

    view->tail = p;

    view->count = view->tail->index;
}

void View_print(struct View *view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;

    while (line->next) {
        Line_print(line->next);
        line = line->next;
    }
}

void View_write(struct View *view, FILE *fp) {
    if (view == NULL or fp == NULL)
        return;

    struct Line *line = view->head;

    while (line->next) {
        Line_write(line->next, fp);
        line = line->next;
    }

    int tmp = view->tail->index;
    View_delete_in_range(view, view->head->index + 1, view->tail->index);
    view->head->index = tmp;
    // printf("\tcount %d\n", view->count);
    // printf("\tindex %d\n", view->head->index);
    // test(view);
}

void View_clear(struct View *view) {
    if (view == NULL)
        return;
    
    View_delete_in_range(view, view->head->index + 1, view->tail->index);
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

int View_read(struct View *view, FILE *fp) {
    char *buf = (char *) malloc(ONCE_READ_SIZE + 1);
    if (buf == NULL) {
        perror("View_read malloc failed\n");
        exit(1);
    }

    int count = 0;
    while (view->size < VIEW_READ_MAX_SIZE and fgets(buf, ONCE_READ_SIZE, fp) != NULL) {
        buf[ONCE_READ_SIZE] = '\0';
        View_append_with_text(view, buf);
        count++;
    }

    free(buf);
    return count;
}

void View_append(struct View *view, struct Line *line) {
    if (view == NULL or line == NULL)
        return;

    // struct Line *p = View_get_line_by_index(view, view->size);
    struct Line *p = view->tail;
    if (p == NULL)
        return;
    p->next = line;
    line->next = NULL;
    p->next->index = p->index + 1;
    view->size++;

    view->tail = line;
    view->count = view->tail->index;
}

void View_append_with_text(struct View *view, char const *buf) {
    if (view == NULL)
        return;
    struct Line *line = Line_create_with_text(buf);
    View_append(view, line);
    // test(view);
}

void View_update_tail(struct View *view) {
    if (view == NULL)
        return;

    view->tail = View_get_line_by_index(view, view->size);
}
