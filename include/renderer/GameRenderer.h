#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "Board.h"
#include "Piece.h"

/**
 * @file GameRenderer.h
 * @brief High-performance terminal rendering system for Tetris, featuring
 * double-buffered incremental updates, widescreen layout (Hold, Matrix, Queue, Stats),
 * and zero-flicker frames.
 */

/**
 * @brief Prepares state parameters, clears terminal buffers, and triggers initial visual draws.
 */
void renderer_init(void);

/**
 * @brief Re-evaluates active grid cells, dirty-checks panel metrics, and performs high-speed
 * updates of Hold, Board Matrix, Queue, and Sidebar regions.
 * * @param b Pointer to the stable game Board.
 * @param current Pointer to the active player Piece.
 * @param hold Pointer to the currently held Piece (can be NULL).
 * @param next_pieces Pointer to the array of upcoming Pieces in the queue (can be NULL).
 * @param next_count Number of upcoming pieces to render (up to 5).
 * @param score Current points accumulated.
 * @param level Game difficulty level.
 * @param lines Cleaned line count totals.
 */
void renderer_draw(const Board *b, const Piece *current, const Piece *hold, 
                   const Piece *next_pieces, int next_count, 
                   int score, int level, int lines);

/**
 * @brief Overlays elegant game-over panel and prints final accumulated score.
 * @param score Ultimate accumulated game points.
 */
void renderer_game_over(unsigned long long score);

#endif /* GAME_RENDERER_H */