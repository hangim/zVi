#include <stdio.h>

#include "string.h"

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
    
    String_output(s);

    String_destory(s);
    s = NULL;
}

int main() {

    String_test();

    return 0;
}
