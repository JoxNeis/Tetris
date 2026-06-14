#include "Board.h"
#include <string.h>

void board_init(Board *b) {
    memset(b->cells, 0, sizeof(b->cells));
}

int board_is_cell_set(const Board *b, int row, int col) {
    if (row < 0 || row >= BOARD_HEIGHT || col < 0 || col >= BOARD_WIDTH)
        return 1;
    return b->cells[row][col] != 0;
}

void board_set_cell(Board *b, int row, int col, int color) {
    if (row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH)
        b->cells[row][col] = color;
}

int board_clear_full_lines(Board *b) {
    int cleared = 0;
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        int full = 1;
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (b->cells[row][col] == 0) { full = 0; break; }
        }
        if (!full) continue;
        for (int r = row; r > 0; r--)
            memcpy(b->cells[r], b->cells[r - 1], sizeof(b->cells[r]));
        memset(b->cells[0], 0, sizeof(b->cells[0]));

        cleared++;
        row++;
    }
    return cleared;
}
