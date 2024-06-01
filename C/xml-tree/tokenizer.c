#include "collector.h"
#include "tokenizer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// === Helper functions for the Collector ADT =================================

// print_char(v) prints the char that v points at.
// effects:  writes to output
// time:     O(1)
void print_char(const void *v) {
    assert(v);
    const char *ch = v;
    if (*ch >= ' ') {
        printf("'%c'", *ch);
    } else if (*ch == '\n') {
        printf("'\\n'");
    } else {
        printf("'\\%d'", *ch);
    }
}

// print_str(v) prints the string that v points at.
// effects:  writes to output
// time:     O(n), where n is the string length
void print_str(const void *v) {
    assert(v);
    char * const *str = v;
    const char *ch = *str;
    printf("\"");
    while (*ch != '\0') {
        if (*ch == '\n') {
            printf("\\n");
        } else {
            printf("%c", *ch);
        }
        ++ch;
    }
    printf("\"");
}

// === The Tokenizer ==========================================================

const char NULL_TERMINATOR = '\0';

// get_token(reading_content, read_success) reads a token from input and return as a string
// effects: reads from input
// time: O(n), where n is the length of the token
static char *get_token(bool reading_content, bool *read_success) {
    assert(read_success);
    const char MARKUP_START = '<';
    int len = 0;
    bool empty_content = true;
    char c = '\0';
    struct collector *single = collector_init(sizeof(char), print_char);
    if (!reading_content) {
        *read_success = (scanf(" %c", &c) > 0);
    } else {
        *read_success = (scanf("%c", &c) > 0);
    }
    if (!reading_content && *read_success) {
        collector_insert(single, &MARKUP_START);
    }
    while (*read_success) {
        if (c == '\n') {
            *read_success = (scanf("%c", &c) > 0);
            continue;
        }
        if (c != ' ' && c != '<' && reading_content) {
            empty_content = false;
        }
        if (c == '<') {
            if (reading_content) {
                collector_insert(single, &NULL_TERMINATOR);
                break;
            } else {
                *read_success = (scanf("%c", &c) > 0);
                continue;
            }
        } else if (c == '>') {
            collector_insert(single, &c);
            collector_insert(single, &NULL_TERMINATOR);
            break;
        } else {
            collector_insert(single, &c);
            *read_success = (scanf("%c", &c) > 0);
        } 
    }
    if ((empty_content && reading_content) || !(*read_success)) {
        free(collector_collapse(single, &len));
        return NULL;
    } else {
        return collector_collapse(single, &len);
    }
}

// tokenize_input(len) reads all input, breaks it into tokens of markup or
//   content, and returns an array of tokens. The length of the returned array
//   is stored in *len.
// effects:  allocates heap memory [client must free the array and each token]
//           mutates *len
//           reads from input
// time:     O(m * n), where m is the number of tokens and n is the length of a single token
char **tokenize_input(int *len) {
    assert(len);
    struct collector *tokens = collector_init(sizeof(char *), print_str);
    bool reading_content = false;
    bool read_success = false;
    while (true) {
        char *token = get_token(reading_content, &read_success);
        reading_content = !reading_content;
        if (!read_success) {
            break;
        } else if (token == NULL) {
            continue;
        } else {
            collector_insert(tokens, &token);
        }
    }
    return collector_collapse(tokens, len);
}