#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"

#define NEXT_QUEUE_SIZE 5

typedef enum {
    GAME_RUNNING,
    GAME_OVER
} GameState;

typedef struct {
    Board     board;
    Piece     current;
    Piece     queue[NEXT_QUEUE_SIZE]; /* visible upcoming pieces             */
    Piece     hold;                   /* held piece (type == -1 if empty)   */
    int       hold_active;            /* 1 if hold slot is occupied         */
    int       hold_used;              /* 1 if hold was already used this turn*/
    GameState state;
    int       score;
    int       level;
    int       lines_cleared;
    int       tick_ms;                /* milliseconds between gravity ticks */
} Game;

void game_init(Game *g);
void game_run (Game *g);  /* blocking main loop */

#endif