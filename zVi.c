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

struct Line_node {
    int index;
    // TODO data
    struct Line_node *next;
};

struct Line {
    struct Line_node *head;
    int size;
};



int main(int argc, char const *argv[]) {

    // String_test();
    
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



struct Line_node * Line_create_node() {
    struct Line_node * node = (struct Line_node *) malloc(sizeof(struct Line_node));
    if (node == NULL)
        ; // TODO

    node->index = 0; // TODO
    node->next = NULL;
}

struct Line * Line_create() {
    struct Line *line = (struct Line *) malloc(sizeof(struct Line));
    if (line == NULL)
        ; // TODO

    line ->head = Line_create_node();
    if (line->head == NULL)
        ; // TODO

    line->size = 0;
    return line;
}

Line_node * Line_get_node_by_index(Line *line, int pos) {
    if (line == NULL)
        ; // TODO
    if (pos <= 0 or pos > line->size)
        return NULL;

    struct Line_node *p = line->head;

    if (pos == 0)
        return p;

    while (p->next->index != pos)
        p = p->next;

    return p;
}

void Line_insert(Line *line, Line_node *node, int pos) {
    
    struct Line_node *p = Line_get_node_by_index(line, pos);
    if (p == NULL)
        ; // TODO

    struct Line_node *tmp = p->next;
    p->next = node;
    node->next = tmp;
    line->size++;
    
    while (p->next) {
        p->next->index = p->index + 1;
        p = p->next;
    }
}

void Line_delete(Line *line, int pos) {
    struct Line_node *p, *q;

    p = Line_get_node_by_index(line, pos - 1);
    if (p == NULL)
        ; // TODO

    q = p->next;

    free(q); // TODO

    p->next = q->next;
}
