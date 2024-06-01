#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "grid.h"

const int GRID_MAX_SIZE = 100;

struct grid grid_create(int rows, int cols) {
    assert(rows > 0);
    assert(cols > 0);
    assert(rows * cols <= GRID_MAX_SIZE);
    struct grid g;
    g.rows = rows;
    g.cols = cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            g.data[i * cols + j] = 0;
        }
    }
    g.max_size = rows * cols;
    return g;
}

int grid_rows(const struct grid *g) {
    assert(g);
    return g -> rows;
}

int grid_cols(const struct grid *g) {
    assert(g);
    return g -> cols;
}

bool grid_get(const struct grid *g, int row, int col, int *val) {
    assert(g);
    assert(val);
    if (row < 0 || row >= grid_rows(g) || col < 0 || col >= grid_cols(g)) {
        return false;
    } else {
        *val = g -> data[row * grid_cols(g) + col];
        return true;
    }
}

bool grid_set(struct grid *g, int row, int col, int value) {
    assert(g);
    if (row < 0 || row >= grid_rows(g) || col < 0 || col >= grid_cols(g)) {
        return false;
    } else {
        g -> data[row * grid_cols(g) + col] = value;
        return true;
    }
}

bool grid_resize(struct grid *g, int rows, int cols) {
    assert(g);
    assert(rows > 0);
    assert(cols > 0);
    if (rows * cols > GRID_MAX_SIZE) {
        return false;
    }
    int min_rows = 0;
    if (rows < grid_rows(g)) {
        min_rows = rows;
    } else {
        min_rows = grid_rows(g);
    }
    int min_cols = 0;
    if (cols < grid_cols(g)) {
        min_cols = cols;
    } else {
        min_cols = grid_cols(g);
    }
    struct grid temp = grid_create(min_rows, min_cols);
    for (int i = 0; i < grid_rows(&temp); i++) {
        for (int j = 0; j < grid_cols(&temp); j++) {
            int temp_value = 0;
            if (grid_get(g, i, j, &temp_value)) {
                grid_set(&temp, i, j, temp_value);
            }
        }
    }
    g -> rows = rows;
    g -> cols = cols;
    g -> max_size = rows * cols;
    for (int i = 0; i < grid_rows(g); i++) {
        for (int j = 0; j < grid_cols(g); j++) {
            int temp_value = 0;
            if (grid_get(&temp, i, j, &temp_value)) {
                grid_set(g, i, j, temp_value);
            } else {
                grid_set(g, i, j, 0);
            }
        }
    }
    return true;
}

// max_len(g) returns the maximum length of the number in the grid g
// requires: g must be valid grid
static int max_len(const struct grid *g) {
    assert(g);
    int max = 0;
    for (int i = 0; i < grid_rows(g); i++) {
        for (int j = 0; j < grid_cols(g); j++) {
            int temp = g -> data[i * grid_cols(g) + j];
            int count = 0;
            if (temp < 0) {
                temp = -temp;
                count++;
            }
            while (temp > 0) {
                temp = temp / 10;
                count++;
            }
            if (count > max) {
                max = count;
            }
        }
    }
    return max;
}

// Additional specifications:
// * all columns shall have the width of the widest number
// * there shall be exactly one additional space separating numbers
// Examples:
// [0 0]       <- column width: 1
// [ 0 42]     <- column width: 2
// [42  2]     <- column width: 2
// [-2  2]     <- column width: 2
// [ 2 -2]     <- column width: 2
// [  0 -42]   <- column width: 3
// [ 136 -136] <- column width: 4
// [-136  136] <- column width: 4
void grid_print(const struct grid *g) {
    assert(g);
    for (int i = 0; i < grid_rows(g); i++) {
        int max = max_len(g);
        printf("[");
        for (int j = 0; j < grid_cols(g); j++) {
            printf("%*d", max, g -> data[i * grid_cols(g) + j]);
            if (j != grid_cols(g) - 1) {
                printf(" ");
            }
        }
        printf("]\n");
    }
}