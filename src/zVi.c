#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "zVi.h"

int main(int argc, char const *argv[]) {

    char buf[10][20];
    char tmp[] = "code is poetry!\n";
    for (int i = 0; i < 10; i++) {
        strncpy(buf[i] + 2, tmp, 20);
        buf[i][0] = '0' + i;
        buf[i][1] = ' ';
        buf[i][19] = '\0';
    }
    printf("ok\n");

    struct Line *line = Line_create();

    for (int i = 0; i < 10; i++) {
        struct Line_node *node = Line_create_node();
        Line_set_string(node, buf[i]);
        Line_insert(line, node, i);
    }

    Line_delete(line, 5);
    
    struct Line_node *p = line->head;
    while (p->next) {
        printf("%2d: ", p->next->index);
        String_output(p->next->string);
        p = p->next;
    }

    return 0;
}
