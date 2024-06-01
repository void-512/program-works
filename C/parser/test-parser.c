#include <stdio.h>
#include "parser.h"

int main(void) {
    char code[10000] = {'\0'};
    int code_len = 0;
    while (scanf("%c", code + code_len) != EOF && code_len < 10000) {
        ++code_len;
    }

    remove_comments(code);
    printf("%s", code);
}