#include "parser.h"
#include <stdbool.h>

void remove_comments(char *code) {
    bool slash_comment = false;
    bool block_comment = false;
    bool in_quote = false;
    bool single_quote = false;
    int pos = 0;
    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '\'' && !block_comment && !slash_comment && !in_quote) {
            single_quote = !single_quote;
        }
        if (code[i] == '\"' && !block_comment && !slash_comment && !single_quote) {
            in_quote = !in_quote;
        }
        if (code[i] == '/' && code[i + 1] == '/' && !block_comment && !slash_comment && !in_quote) {
            slash_comment = true;
        }
        if (slash_comment && code[i] == '\n') {
            slash_comment = false;
        }
        if (code[i] == '/' && code[i + 1] == '*' && !block_comment && !slash_comment && !in_quote) {
            block_comment = true;
        }
        if (block_comment && code[i] == '*' && code[i + 1] == '/') {
            block_comment = false;
            i += 2;
        }
        if (!slash_comment && !block_comment) {
            code[pos] = code[i];
            pos++;
        }
    }
    code[pos] = '\0';
}