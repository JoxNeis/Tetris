#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"

typedef enum {
    GAME_RUNNING,
    GAME_OVER
} GameState;

typedef struct {
    Board     board;
    Piece     current;
    Piece     next;
    GameState state;
    int       score;
    int       level;
    int       lines_cleared;
    int       tick_ms;     /* milliseconds between gravity ticks */
} Game;

void game_init (Game *g);
void game_run  (Game *g);   /* blocking main loop */

#endif
