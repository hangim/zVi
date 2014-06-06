/******************************************************************************
 *
 * Filename:
 *  view.h
 *
 * Description:
 *  视图相关
 *
 ******************************************************************************/

#ifndef zVi_VIEW
#define zVi_VIEW

#include "line.h"

#define VIEW_ACTIVE_MAX_LINE 100
#define VIEW_READ_MAX_LINE 80
#define ONCE_READ_SIZE 320

struct View {
    int size;
    int count;
    struct Line *head;
    struct Line *tail;
    FILE *fp_from;
    FILE *fp_to;
};

struct View *View_create(FILE * const fp_from, FILE * const fp_to);
struct Line *View_get_line_by_index(const struct View * const view, const int pos);
void View_update_tail(struct View * const view);
void View_append(struct View * const view, struct Line * const line);
void View_append_with_text(struct View * const view, const char *buf);
void View_insert(struct View * const view, struct Line * const line, const int pos);
void View_insert_with_text(struct View * const view, const char *buf, const int pos);
void View_delete_by_index(struct View * const view, const int pos);
void View_delete_in_range(struct View * const view, const int from, const int end);
void View_print(const struct View * const view);
int  View_read(struct View * const view);
void View_write(struct View * const view);
void View_write_first_line(struct View * const view);
void View_clear(struct View * const view);
void View_destory(struct View * const view);

#endif