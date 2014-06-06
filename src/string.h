/******************************************************************************
 *
 * Filename:
 *  string.h
 *
 * Description:
 *   字符块链表相关
 *
 ******************************************************************************/

#ifndef zVi_STRING
#define zVi_STRING

#define STRING_MAX_SIZE 80

struct String {
    char *s;
    struct String *next;
};

struct String *String_create_node(const char * const buf);
struct String *String_create(const char *buf);
void String_print(const struct String * const head);
void String_write(const struct String * const head, FILE * const fp);
void String_destory(struct String * const head);

#endif