/******************************************************************************
 *
 * Filename:
 *  line.h
 *
 * Description:
 *   行相关
 *
 ******************************************************************************/

#ifndef zVi_LINE
#define zVi_LINE

#include "string.h"

struct Line {
    int index;
    struct String *string;
    struct Line *next;
};

struct Line *Line_create();
void Line_set_index(struct Line * const line, const int index);
void Line_set_text(struct Line * const line, const char *buf);
struct Line *Line_create_with_text(const char *buf);
void Line_print(const struct Line * const line);
void Line_write(const struct Line * const line, FILE * const fp);
void Line_destory(struct Line * const line);

#endif
