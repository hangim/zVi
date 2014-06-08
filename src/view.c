#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <windows.h>

#include "view.h"

struct View *View_create(FILE * const fp_from, FILE * const fp_to) {
    if (fp_from == NULL or fp_to == NULL)
        return NULL;

    struct View *view = (struct View *) malloc(sizeof(struct View));
    if (view == NULL) {
        perror("View_create malloc failed\n");
        exit(1);
    }

    view->fp_from = fp_from;
    view->fp_to = fp_to;

    view->head = view->tail = Line_create();
    view->size = 0;
    view->count = 0;

    return view;
}

struct Line *View_get_line_by_index(const struct View * const view, const int pos) {
    if (view == NULL)
        return NULL;

    if (pos < view->head->index or pos > view->tail->index)
        return NULL;

    struct Line *line = view->head;

    while (line and line->index != pos)
        line = line->next;

    return line;
}

void View_update_tail(struct View * const view) {
    if (view == NULL)
        return;

    view->tail = View_get_line_by_index(view, view->size);
}

void View_append(struct View * const view, struct Line * const line) {
    if (view == NULL or line == NULL)
        return;

    view->tail->next = line;
    line->index = view->tail->index + 1;
    view->tail = line;
    view->size++;
    view->count = view->tail->index;

    if (view->size > VIEW_ACTIVE_MAX_LINE) {
        View_write_first_line(view);
    }
}

void View_append_with_text(struct View * const view, const char *buf) {
    if (view == NULL or buf == NULL)
        return;
    struct Line *line = Line_create_with_text(buf);
    View_append(view, line);
}

void View_insert(struct View * const view, struct Line * const line, const int pos) {
    if (view == NULL or line == NULL)
        return;

    struct Line *p = View_get_line_by_index(view, pos);
    if (p == NULL)
        return;

    line->next = p->next;
    p->next = line;
    
    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }

    view->tail = p;

    view->size++;
    view->count = view->tail->index;

    if (view->size > VIEW_ACTIVE_MAX_LINE) {
        View_write_first_line(view);
    }
}

void View_insert_with_text(struct View * const view, const char *buf, const int pos) {
    if (view == NULL or buf == NULL or pos < view->head->index or pos > view->tail->index)
        return;

    struct Line *line = Line_create_with_text(buf);
    View_insert(view, line, pos);
}

void View_delete_by_index(struct View * const view, const int pos) {
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

void View_delete_in_range(struct View * const view, const int from, const int end) {
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

void View_print(const struct View * const view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;

    int c = 0;
    while (line->next) {
        Line_print(line->next);
        line = line->next;
        c++;
        if (c == 20 and line->next) {
            c = 0;
            printf("\n-- More --");
            if (getch() == 'q') {
                return;
            } else {
                system("cls");
            }
        }
    }
}

int View_read(struct View * const view) {
    char *buf = (char *) malloc(ONCE_READ_SIZE + 1);
    if (buf == NULL) {
        perror("View_read malloc failed\n");
        exit(1);
    }

    int count = 0;
    while (view->size < VIEW_READ_MAX_LINE and fgets(buf, ONCE_READ_SIZE, view->fp_from) != NULL) {
        buf[ONCE_READ_SIZE] = '\0';
        View_append_with_text(view, buf);
        count++;
    }

    free(buf);
    return count;
}

void View_write(struct View * const view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;

    while (line->next) {
        Line_write(line->next, view->fp_to);
        line = line->next;
    }

    int tmp = view->count;
    View_delete_in_range(view, view->head->index + 1, view->tail->index);
    view->count = view->head->index = tmp;
}

void View_write_first_line(struct View * const view) {
    if (view == NULL or view->size == 0)
        return;

    struct Line *tmp = view->head->next;
    if (tmp == NULL)
        return;

    view->head->next = tmp->next;
    view->head->index = tmp->index;
    Line_write(tmp, view->fp_to);
    Line_destory(tmp);
}

void View_clear(struct View * const view) {
    if (view == NULL)
        return;
    
    View_delete_in_range(view, view->head->index + 1, view->tail->index);
}

void View_destory(struct View * const view) {
    if (view == NULL)
        return;

    struct Line *line = view->head;
    while (line) {
        struct Line *tmp = line;
        line = line->next;
        Line_destory(tmp);
    }

    free(view);
}