#ifndef zVi_STRING
#define zVi_STRING

#define STRING_MAX_SIZE 80

struct String {
    char *s;
    struct String *next;
};

struct String *String_create_node(char const *buf);
struct String *String_create(char const *buf);
void String_output(struct String *head);
void String_destory(struct String *head);

#endif