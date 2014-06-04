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
void String_output(struct String * string);
void String_clear (struct String * string);
void String_destory (struct String * string);



struct Line_node {
    int index;
    struct String *string;
    struct Line_node *next;
};

struct Line {
    struct Line_node *head;
    int size;
};

struct Line_node * Line_create_node();
void Line_set_string(struct Line_node *node, char const *buf);
struct Line * Line_create();
struct Line_node * Line_get_node_by_index(struct Line *line, int pos);
void Line_insert(struct Line *line, struct Line_node *node, int pos);
void Line_delete(struct Line *line, int pos);



int main(int argc, char const *argv[]) {

    char buf[] = "code is poetry!\n";

    struct Line *line = Line_create();

    for (int i = 0; i < 10; i++) {
        struct Line_node *node = Line_create_node();
        Line_set_string(node, buf);
        Line_insert(line, node, 0);
    }
    
    struct Line_node *p = line->head;
    while (p->next) {
        printf("%2d: ", p->next->index);
        String_output(p->next->string);
        p = p->next;
    }

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

void String_output(struct String * string) {
    if (string == NULL)
        return;

    struct String *p = string;

    while (p->next) {
        printf("%s", p->next->s);
        p = p->next;
    }
}

void String_clear (struct String * head) {
    struct String *p, *q;
    p = q = head->next;
    while (p) {
        q = p->next;
        free(p->s);
        free(p);
        p = q;
    }
    head->next = NULL;
}

void String_destory (struct String * string) {
    if (string == NULL)
        return;

    struct String  *p, *q;
    p = q = string;
    while (p) {
        q = p->next;
        free(p->s);
        free(p);
        p = q;
    }
}



struct Line_node * Line_create_node() {
    struct Line_node * node = (struct Line_node *) malloc(sizeof(struct Line_node));
    if (node == NULL)
        ; // TODO

    node->string = NULL;
    node->index = 0; // TODO
    node->next = NULL;

    return node;
}

void Line_set_string(struct Line_node *node, char const *buf) {
    if (node->string != NULL)
        String_destory(node->string);

    node->string = String_create(buf);
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

struct Line_node * Line_get_node_by_index(struct Line *line, int pos) {
    if (line == NULL)
        ; // TODO
    if (pos < 0 or pos > line->size)
        return NULL;

    struct Line_node *p = line->head;

    if (pos == 0)
        return p;

    while (p->next->index != pos)
        p = p->next;

    return p;
}

void Line_insert(struct Line *line, struct Line_node *node, int pos) {
    
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

void Line_delete(struct Line *line, int pos) {
    struct Line_node *p, *q;

    p = Line_get_node_by_index(line, pos - 1);
    if (p == NULL)
        ; // TODO

    q = p->next;

    free(q); // TODO

    p->next = q->next;
}
