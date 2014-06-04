#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_MAX_SIZE 80
struct String {
    char *s;
    struct String *next;
};

struct String * create_String_node(char const *buf) {
    struct String *s = (struct String *) malloc(sizeof(struct String));
    
    if (buf == NULL) { // head node
        s->s = NULL;
    } else {
        s->s = (char *) malloc(STRING_MAX_SIZE + 1);
        strncpy(s->s, buf, STRING_MAX_SIZE);
        s->s[STRING_MAX_SIZE] = '\0';
    }
    
    s->next = NULL;

    return s;
}

struct String * create_String (char const *buf) {
    if (buf == NULL)
        return NULL;

    int len = strlen(buf);
    struct String *head, *p;
    head = p = create_String_node(NULL);

    while (len > 0) {
        p->next = create_String_node(buf);
        len -= STRING_MAX_SIZE;
        buf += STRING_MAX_SIZE;
        p = p->next;
    }

    return head;
}



int main(int argc, char const *argv[]) {

    char buf[] = "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n"
        "hello world " "hello world " "hello world " "hello world " "hello world\n";

    struct String *s = create_String(buf);

    while (s->next) {
        printf("%s", s->next->s);
        s = s->next;
    }

    return 0;
}
