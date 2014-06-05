#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "zVi.h"

void zVi_insert();
void zVi_delete();
void zVi_print();
void zVi_next_page();
void zVi_quit();

FILE *f_from;
FILE *f_to;
struct View *view;
char buf[COMMAND_SIZE + 1];

int main(int argc, char const *argv[]) {

    if (argc != 3)
        return -1; // TODO

    f_from = fopen(argv[1], "r");
    f_to = fopen(argv[2], "w");
    view = View_create();

    // TODO command
    View_read(view, f_from);
    zVi_print(view);

    while (fgets(buf, COMMAND_SIZE, stdin)) {
        switch (buf[0]) {
            case 'i' :
                zVi_insert();
                break;
            
            case 'd' :
                zVi_delete();
                break;
        
            case 'n' :
                zVi_next_page();
                break;
        
            case 'p' :
                zVi_print();
                break;
        
            case 'q': 
                zVi_quit();
                break;
        }
    }

    return 0;
}

void zVi_insert() {
    system("cls");
    int pos;
    sscanf(buf + 1, "%d", &pos);
    fgets(buf, COMMAND_SIZE, stdin);
    buf[COMMAND_SIZE] = '\0';
    View_insert_with_text(view, buf, pos);
    View_print(view);
}

void zVi_delete() {
    system("cls");
    int from, end;
    int num = sscanf(buf + 1, "%d%d", &from, &end);
    if (num == 2) {
        View_delete_in_range(view, from, end);
    } else if (num == 1) {
        View_delete_by_index(view, from);
    } else {
        ; // TODO
    }
    View_print(view);
}

void zVi_print() {
    system("cls");
    View_print(view);
}

void zVi_next_page() {
    system("cls");
    View_write(view, f_to);
    if (View_read(view, f_from) != 0)
        View_print(view);
    else
        printf("file read end\n");
}

void zVi_quit() {
    system("cls");
    do {
        View_write(view, f_to);
    } while (View_read(view, f_from) != 0);

    if (f_from)
        fclose(f_from);
    if (f_to)
        fclose(f_to);

    exit(0);
}
