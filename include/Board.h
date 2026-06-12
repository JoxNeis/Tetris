#ifndef BOARD_H
#define BOARD_H

#define BOARD_WIDTH  10
#define BOARD_HEIGHT 20

typedef struct {
    int cells[BOARD_HEIGHT][BOARD_WIDTH];
} Board;

void  board_init(Board *b);
int   board_is_cell_set(const Board *b, int row, int col);
void  board_set_cell(Board *b, int row, int col, int color);
int   board_clear_full_lines(Board *b);  /* returns number of lines cleared */

#endif
