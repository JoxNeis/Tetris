#include "Piece.h"
#include <string.h>

void piece_spawn(Piece *p, TetrominoType type) {
    p->type      = type;
    p->tetromino = get_tetromino_by_type(type);
    p->rotation  = 0;
    p->row       = 0;
    p->col       = BOARD_WIDTH / 2 - 2;
}

void piece_get_shape(const Piece *p, int out[4][4]) {
    get_rotation_shape(p->tetromino, p->rotation, out);
}

int piece_is_valid(const Piece *p, const Board *b) {
    int shape[4][4];
    piece_get_shape(p, shape);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (!shape[r][c]) continue;
            int br = p->row + r;
            int bc = p->col + c;
            if (br < 0 || br >= BOARD_HEIGHT) return 0;
            if (bc < 0 || bc >= BOARD_WIDTH)  return 0;
            if (b->cells[br][bc] != 0)         return 0;
        }
    }
    return 1;
}

int piece_move_left(Piece *p, const Board *b) {
    p->col--;
    if (!piece_is_valid(p, b)) { p->col++; return 0; }
    return 1;
}

int piece_move_right(Piece *p, const Board *b) {
    p->col++;
    if (!piece_is_valid(p, b)) { p->col--; return 0; }
    return 1;
}

int piece_move_down(Piece *p, const Board *b) {
    p->row++;
    if (!piece_is_valid(p, b)) { p->row--; return 0; }
    return 1;
}

void piece_rotate(Piece *p, const Board *b) {
    int old = p->rotation;
    p->rotation = (p->rotation + 1) % 4;
    if (!piece_is_valid(p, b)) {
        p->col--;
        if (!piece_is_valid(p, b)) {
            p->col++;
            p->col++;
            if (!piece_is_valid(p, b)) {
                p->col--;
                p->rotation = old;
            }
        }
    }
}

void piece_lock(const Piece *p, Board *b) {
    int shape[4][4];
    piece_get_shape(p, shape);
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (shape[r][c])
                board_set_cell(b, p->row + r, p->col + c, p->tetromino->color);
}
