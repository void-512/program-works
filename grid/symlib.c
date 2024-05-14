#include "symlib.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

static int len;
static const char *sym[CAP];

const int read_symbol() {
    char str[SYMCAP];
    scanf("%s", str);
    for (int i = 0; i < len; i++) {
        if (!strcmp(str, sym[i])) {
            return i;
        }
    }
    return INVALID_SYMBOL;
}

const int lookup_symbol(const char *s) {
    assert(len < CAP);
    sym[len] = s;
    len++;
    return len - 1;
}

void printsym() {
    for (int i = 0; i < len; i++) {
        printf("%s\n", sym[i]);
    }
}