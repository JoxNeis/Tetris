#ifndef PIECE_H
#define PIECE_H

#include "Tetromino.h"
#include "Board.h"

/* Represents the active (falling) piece */
typedef struct {
    const Tetromino *tetromino; /* pointer to shape data                  */
    TetrominoType    type;      /* which piece type                        */
    int              rotation;  /* 0-3                                     */
    int              row;       /* top-left origin row on the board        */
    int              col;       /* top-left origin col on the board        */
} Piece;

void piece_spawn  (Piece *p, TetrominoType type);
void piece_get_shape(const Piece *p, int out[4][4]);

/* Returns 1 if the piece can occupy its current position on the board */
int  piece_is_valid(const Piece *p, const Board *b);

/* Movement helpers – each returns 1 on success, 0 if blocked */
int  piece_move_left (Piece *p, const Board *b);
int  piece_move_right(Piece *p, const Board *b);
int  piece_move_down (Piece *p, const Board *b);
void piece_rotate    (Piece *p, const Board *b);

/* Lock the piece's cells into the board */
void piece_lock(const Piece *p, Board *b);

#endif
