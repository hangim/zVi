#ifndef zVi_VIEW
#define zVi_VIEW

#include "line.h"

#define VIEW_READ_MAX_SIZE 20
#define ONCE_READ_SIZE 320

struct View {
    int size;
    struct Line *head;
    struct Line *tail;
};

struct View *View_create();
struct Line *View_get_line_by_index(struct View *view, int pos);
void View_insert(struct View *view, struct Line *line, int pos);
void View_insert_with_text(struct View *view, char const *buf, int pos);
void View_delete_by_index(struct View *view, int pos);
void View_delete_in_range(struct View *view, int from, int end);
void View_print(struct View *view);
void View_write(struct View *view, FILE *fp);
void View_clear(struct View *view);
void View_destory(struct View *view);
void View_read(struct View *view, FILE *fp);
void View_append(struct View *view, struct Line *line);
void View_append_with_text(struct View *view, char const *buf);
void View_update_tail(struct View *view);

#endif