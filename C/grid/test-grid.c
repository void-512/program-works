#include "grid.h"
#include "symlib.h"
#include <assert.h>
#include <stdio.h>

// The following commands are available:
// RESIZE <rows:int> <cols:int>
//            Resizes the grid to rows rows and cols columns. Both rows and
//            cols must be positive, and the product of rows and cols must not
//            exceed 100.
// SET <row:int> <col:int> <val:int>
//            Sets the element at row row and column col to val.
// GET <row:int> <col:int>
//            Returns the element at row row and column col.
// PRINT      Prints out the content of the grid.
// DIMENSIONS Prints out the dimensions of the grid.
int main(void) {
    const int CMD_RESIZE = lookup_symbol("RESIZE");
    const int CMD_SET = lookup_symbol("SET");
    const int CMD_GET = lookup_symbol("GET");
    const int CMD_PRINT = lookup_symbol("PRINT");
    const int CMD_DIMENSIONS = lookup_symbol("DIMENSIONS");

    struct grid g = grid_create(1,1);
    int cmd = INVALID_SYMBOL;

    while ((cmd = read_symbol()) != INVALID_SYMBOL) {
        if (CMD_PRINT == cmd) {
            grid_print(&g);
        } else if (CMD_DIMENSIONS == cmd) {
            printf("Grid size is %d x %d.\n", grid_rows(&g), grid_cols(&g));
        } else {
            int row = 0;
            int col = 0;
            if (scanf("%d %d", &row, &col) != 2) {
                break;
            }
            if (CMD_RESIZE == cmd) {
                if (grid_resize(&g, row, col)) {
                    printf("New grid size is %d x %d.\n", grid_rows(&g), grid_cols(&g));
                } else {
                    printf("Warning: resizing grid failed\n");
                }
            } else if (CMD_SET == cmd) {
                int val = 0;
                if (scanf("%d", &val) != 1) {
                    break;
                }
                if (grid_set(&g, row, col, val)) {
                    printf("Setting grid value at (%d,%d) to %d.\n", row, col, val);
                } else {
                    printf("Warning: setting value in grid failed\n");
                }
            } else if (CMD_GET == cmd) {
                int val = 0;
                if (grid_get(&g, row, col, &val)) {
                    printf("Grid value at (%d,%d) is %d.\n", row, col, val);
                } else {
                    printf("Warning: getting value from grid failed\n");
                }
            } else {
                printf("ERROR: unknown command\n");
                break;
            }
        }
    }
}