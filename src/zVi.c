#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iso646.h>
#include <conio.h>

#include "zVi.h"

void zVi_help();
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
    system("title=zVi");
    system("color 0e");

    if (argc != 3) {
        printf("usage: zVi input output\n");
        exit(0);
    }

    f_from = fopen(argv[1], "r");
    f_to = fopen(argv[2], "w");
    if (f_from == NULL or f_to == NULL) {
        perror("open file failed\n");
        exit(1);
    }

    view = View_create(f_from, f_to);

    // TODO command
    View_read(view);
    zVi_help();

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

            case 'h':
                zVi_help();
                break;

            default:
                printf("==>");
        }
    }

    return 0;
}

void zVi_help() {
    system("cls");
    printf(
        "zVi\n"
        "===\n"
        "a simple text edit program\n\n"

        "command:\n"
        "---\n"
        "i <行号> <回车> <文本> <回车>\n"
        "\t将<文本>插入活区中第<行号>行之后。\n"

        "d <行号1> [<空格> <行号2> ] <回车>\n"
        "\t删除活区中第<行号1>行（到<行号2>行）\n"

        "n <回车>\n"
        "\t将活区写入输出文件，并从输入文件中读入下一段，作为新的活区。\n"

        "p <回车>\n"
        "\t逐页（每页20行）显示活区内容\n"

        "q <回车>\n"
        "\t保存并退出\n"

        "h <回车>\n"
        "\t查看帮助\n"

        "\n==>"
        );
}

void zVi_insert() {
    int pos;
    sscanf(buf + 1, "%d", &pos);
    fgets(buf, COMMAND_SIZE, stdin);
    buf[COMMAND_SIZE] = '\0';
    View_insert_with_text(view, buf, pos);
    zVi_print(view);
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
    zVi_print(view);
}

void zVi_print() {
    system("cls");
    View_print(view);
    printf("\n==>");
}

void zVi_next_page() {
    system("cls");
    View_write(view);
    if (View_read(view) != 0)
        zVi_print(view);
    else {
        printf("文件已读取完毕, 按任意键退出\n");
        getch();
        zVi_quit();
    }
}

void zVi_quit() {
    system("cls");
    do {
        View_write(view);
    } while (View_read(view) != 0);
    View_destory(view);

    if (f_from)
        fclose(f_from);
    if (f_to)
        fclose(f_to);

    system("color 07");
    system("title=命令提示符");
    exit(0);
}
