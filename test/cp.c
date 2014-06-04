#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    if (argc != 3)
        exit(0); // TODO

    char const *fn_from = argv[1];
    char const *fn_to = argv[2];
    
    FILE *f_from = fopen(fn_from, "r");
    FILE *f_to = fopen(fn_to, "w");

    if (f_from == NULL or f_to == NULL)
        exit(0); // TODO

    char buf[81];
    while (fgets(buf, sizeof(buf), f_from) != NULL) {
        fwrite(buf, strlen(buf), 1, f_to);
    }

    return 0;
}
