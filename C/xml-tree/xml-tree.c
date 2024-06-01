#include "xml-tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "collector.h"
#include <stdbool.h>
#include <string.h>

// Indicates that an XML-node is a text node, i.e., a leaf.
const int TEXT_NODE = -1;

// The label for the root node of the XML tree.
const char *ROOT_TAG =  "<%%root%%>";

// === XML-Tree Nodes =========================================================

// A node in an XML-tree.
struct xnode {
    const char *label;       // token stored in this node
    struct xnode **children; // array of children
    int children_len;        // length of children array, TEXT_NODE if leaf
};

// same_markup(a, b) determines if the strings a and b have the same markup.
// time: O(n) where n is the length of a.
static bool same_markup(const char *a, const char *b) {
    assert(a);
    assert(b);
    if (strlen(a) != strlen(b) - 1) {
        return false;
    }
    if (a[0] != b[0] || b[0] != '<') {
        return false;
    }
    if (b[1] != '/') {
        return false;
    }
    for (int i = 1; i < strlen(a); i++) {
        if (a[i] != b[i + 1]) {
            return false;
        }
    }
    return true;
}

// new_tag(a) determines if the token a is a new tag.
// time: O(1)
static bool new_tag(const char *a) {
    assert(a);
    return *a == '<';
}

// node_print_helper(xn, children_layer) prints out the xnode *xn and its children in the format required.
// effects: writes to output
// time: O(n) where n is the number of nodes in the tree.
static void node_print_helper(const struct xnode *xn, int children_layer) {
    assert(xn);
    for (int i = 0; i < children_layer; i++) {
        printf("  ");
    }
    printf("%s\n", xn -> label);
    for (int i = 0; i < xn -> children_len; i++) {
        node_print_helper(xn -> children[i], children_layer + 1);
    }
    if (new_tag(xn -> label)) {
        for (int i = 0; i < children_layer; i++) {
            printf("  ");
        }
        printf("</%s\n", xn -> label + 1);
    }
}

// node_print(v) prints out the xnode *v.
// effects: writes to output
// time: O(n) where n is the number of nodes in the tree.
void node_print(const void *v) {
    assert(v);
    const struct xnode *xn = v;
    node_print_helper(xn, 0);
}

// tree_create(tokens, len) creates an XML-tree that contains all strings from
//   the array tokens of length len.
// effects: allocates memory [client must call tree_destroy]
// time: O(n) where n is the number of strings in tokens
struct xnode *node_make(const char *label, char ***tokens, int *len) {
    assert(label);
    assert(tokens);
    assert(*tokens);
    assert(len);
    assert(*len >= 0);
    struct xnode *xn = malloc(sizeof(struct xnode));
    struct collector *col = collector_init(sizeof(struct xnode *), node_print);
    assert(col);
    xn -> label = label;
    if (!new_tag(label)) {
        xn -> children = collector_collapse(col, &xn -> children_len);
        xn -> children_len = TEXT_NODE;
        return xn;
    } else {
        while (*len > 0) {
            if (same_markup(label, **tokens)) {
                *tokens += 1;
                *len -= 1;
                break;
            } else {
                const char *next_label = **tokens;
                *tokens += 1;
                *len -= 1;
                struct xnode *next_node = node_make(next_label, tokens, len); 
                collector_insert(col, &next_node);
            }
        }
        xn -> children = collector_collapse(col, &xn -> children_len);
        return xn;
    }
}

// node_destroy(xn) releases all resources use by XML-node *xn, including its
//   children.
// effects: invalidates *xn
// time: O(n) where n is the number of nodes in the tree.
void node_destroy(struct xnode *xn) {
    assert(xn);
    for (int i = 0; i < xn -> children_len; i++) {
        node_destroy(xn -> children[i]);
    }
    free(xn -> children);
    free(xn);
}

// === XML-Tree ===============================================================

struct xtree {
    struct xnode *root; // root of the XML-tree
};

// tree_create(tokens, len) creates an XML-tree that contains all strings from
//   the array tokens of length len.
// effects: allocates memory [client must call tree_destroy]
// time: O(n) where n is the number of strings in tokens
struct xtree *tree_create(char **tokens, int len) {
    assert(tokens);
    struct xtree *tr = malloc(sizeof(struct xtree));  
    assert(tr);
    if (len == 0) {
        tr->root = NULL;
    } else {
        tr->root = node_make(ROOT_TAG, &tokens, &len);
    }
    return tr;
}

// tree_destroy(tr) releases all resources used by XML tree *tr.
// effects: invalidates *tr
// time: O(n) where n is the number of nodes in the tree.
void tree_destroy(struct xtree *tr) {
    assert(tr);
    if (tr->root != NULL) {
        node_destroy(tr->root);
    }
    free(tr);
}

// tree_print(tr) prints out the content of XML tree *tr.
// effects: writes to output
// time: O(n) where n is the number of nodes in the tree.
void tree_print(struct xtree *tr) {
    assert(tr);
    if (tr->root != NULL) {
        node_print(tr -> root);
    } else {
        printf("%s\n</%s\n", ROOT_TAG, ROOT_TAG + 1);
    }
}
