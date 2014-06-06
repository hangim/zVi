/******************************************************************************
 *
 * Filename:
 *  string_test.c
 *
 * Description:
 *   测试字符块链表
 *
 ******************************************************************************/

#include <stdio.h>

#include "string.h"

void String_test();

int main() {

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

    struct String *s;
    s = String_create(buf);
    
    String_print(s);

    FILE *f = fopen("String_write.out", "w");
    String_write(s, f);

    String_destory(s);
    s = NULL;
}
