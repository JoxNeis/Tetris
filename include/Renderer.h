#ifndef RENDERER_H
#define RENDERER_H

#include "Board.h"
#include "Piece.h"

/* Clear terminal screen */
void renderer_clear(void);

/* Draw the board, the active piece, score and level */
void renderer_draw(const Board *b, const Piece *current,
                   int score, int level, int lines);

/* Show game-over screen */
void renderer_game_over(int score);

#endif
