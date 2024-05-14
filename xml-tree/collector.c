#include "collector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// === Collector Nodes ========================================================

// A node in a collector
struct col_node {
    void *data;            // The stored data
    struct col_node *next; // The next node
};

// cnode_create(obj, obj_size) creates a new collector node that stores a copy
//   of the object *obj of size obj_size.
// requires: *obj is of size obj_size [not asserted]
// effects:  allocates heap memory [client must call cnode_destroy]
// time:     O(o), where o is the object size
struct col_node *cnode_create(const void *obj, size_t obj_size) {
    assert(obj);
    struct col_node *cn = malloc(sizeof(struct col_node));
    cn->data = malloc(obj_size);
    assert(cn->data);
    // void *memcpy(void *dest, const void *src, size_t count) copies count
    //   bytes from *src to *dest. Here it is used to copy one object of size
    //   obj_size from *obj into *cn->data. Since memcpy blindly copies a set
    //   amount of bytes, it does not need to know the underlying structure
    //   stored at the source (i.e., *obj).
    memcpy(cn->data, obj, obj_size);
    cn->next = NULL;
    return cn;
}

// cnode_destroy(cn) releases all resources used by *cn directly.
// effects:  invalidates *cn
// time:     O(1)
void cnode_destroy(struct col_node *cn) {
    assert(cn);
    free(cn->data);
    free(cn);
}

// === Collector ==============================================================

struct collector {
    struct col_node *front;          // front node
    int obj_size;                    // size of a single object in bytes
    void (*obj_print)(const void *); // function to print a single object
};

struct collector *collector_init(int obj_size, void (*obj_print)(const void *)) {
    assert(obj_size > 0);
    assert(obj_print);
    struct collector *col = malloc(sizeof(struct collector));
    col -> front = NULL;
    col -> obj_size = obj_size;
    col -> obj_print = obj_print;
    return col;
}

void collector_insert(struct collector *col, const void *obj) {
    assert(col);
    assert(obj);
    struct col_node *temp = col -> front;
    if (!temp) {
        col -> front = cnode_create(obj, col -> obj_size);
        return;
    }
    while (temp -> next) {
        temp = temp -> next;
    }
    temp -> next = cnode_create(obj, col -> obj_size);
}

void *collector_collapse(struct collector *col, int *len) {
    assert(col);
    assert(len);
    int count = 0;
    for (struct col_node *temp = col -> front; temp; temp = temp -> next) {
        count++;
    }
    void *result = malloc(count * col -> obj_size);
    struct col_node *prev = NULL;
    struct col_node *curr = col -> front;
    for (int i = 0; i < count; i++) {
        memcpy(result + i * col -> obj_size, curr -> data, col -> obj_size);
        prev = curr;
        curr = curr -> next;
        cnode_destroy(prev);
    }
    free(col);
    *len = count;
    return result;
}

void collector_print(const struct collector *col) {
    // The print format is: "[OBJECT, OBJECT, OBJECT, ...]\n"
    //   where OBJECT is the printout of an object by col->obj_print,
    //   adjacent OBJECTs are separated by ", ".
    //   If the collector is empty, the function should print: "[]\n"
    assert(col);
    printf("[");
    for (struct col_node *temp = col -> front; temp; temp = temp -> next) {
        col -> obj_print(temp -> data);
        if (temp -> next) {
            printf(", ");
        }
    }
    printf("]\n");
}
