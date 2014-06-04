#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_MAX_SIZE 80
struct String {
    char *s;
    struct String *next;
};

void String_test();
struct String * String_create_node(char const *buf);
struct String * String_create (char const *buf);
void String_destory (struct String * string);


int main(int argc, char const *argv[]) {

    String_test();
    
    return 0;
}


void String_test() {
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

    struct String *s, *p;
    s = p = String_create(buf);

    while (p->next) {
        printf("%s", p->next->s);
        p = p->next;
    }

    String_destory(s);
    s = p = NULL;
}

struct String * String_create_node(char const *buf) {
    struct String *s = (struct String *) malloc(sizeof(struct String));
    if (s == NULL)
        ; // TODO
    
    if (buf == NULL) { // head node
        s->s = NULL;
    } else {
        s->s = (char *) malloc(STRING_MAX_SIZE + 1);
        if (s->s == NULL)
            ; // TODO
        strncpy(s->s, buf, STRING_MAX_SIZE);
        s->s[STRING_MAX_SIZE] = '\0';
    }
    
    s->next = NULL;

    return s;
}

struct String * String_create (char const *buf) {
    if (buf == NULL)
        return NULL;

    int len = strlen(buf);
    struct String *head, *p;
    head = p = String_create_node(NULL);

    while (len > 0) {
        p->next = String_create_node(buf);
        len -= STRING_MAX_SIZE;
        buf += STRING_MAX_SIZE;
        p = p->next;
    }

    return head;
}

void String_destory (struct String * string) {
    if (string == NULL)
        return;

    struct String  *p, *q;
    p = q = string;
    while (p) {
        q = q->next;
        free(p);
        p = q;
    }
}
