#include "Game.h"
#include "Input.h"
#include "renderer/GameRenderer.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static const int SCORE_TABLE[5] = { 0, 100, 300, 500, 800 };

static const int LEVEL_SPEED[] = {
    800, 720, 630, 550, 470, 380, 300, 220, 140, 100,
     80,  70,  60,  50,  40
};
#define MAX_LEVEL 14

static TetrominoType random_type(void) {
    return (TetrominoType)(rand() % 7);
}

static int level_speed(int level) {
    if (level > MAX_LEVEL) level = MAX_LEVEL;
    return LEVEL_SPEED[level];
}

/**
 * @brief Shifts the queue forward and spawns a new tail piece.
 *        Sets game over if the freshly-promoted current piece overlaps existing blocks.
 */
static void advance_queue(Game *g) {
    g->current = g->queue[0];
    for (int i = 0; i < NEXT_QUEUE_SIZE - 1; i++) {
        g->queue[i] = g->queue[i + 1];
    }
    piece_spawn(&g->queue[NEXT_QUEUE_SIZE - 1], random_type());
    if (!piece_is_valid(&g->current, &g->board)) {
        g->state = GAME_OVER;
    }
    g->hold_used = 0;
}

/**
 * @brief Swaps the current piece with the hold slot.
 *        Only one swap is allowed per piece placement (hold_used flag).
 */
static void do_hold(Game *g) {
    if (g->hold_used) return;

    if (!g->hold_active) {
        g->hold        = g->current;
        g->hold_active = 1;
        advance_queue(g);
    } else {
        Piece tmp  = g->hold;
        g->hold    = g->current;
        piece_spawn(&tmp, tmp.type);
        g->current = tmp;
        if (!piece_is_valid(&g->current, &g->board)) {
            g->state = GAME_OVER;
            return;
        }
    }
    g->hold.rotation = 0;
    g->hold.row      = 0;
    g->hold.col      = 0;

    g->hold_used = 1;
}

void game_init(Game *g) {
    srand((unsigned)time(NULL));
    board_init(&g->board);

    g->state         = GAME_RUNNING;
    g->score         = 0;
    g->level         = 1;
    g->lines_cleared = 0;
    g->tick_ms       = level_speed(1);
    g->hold_active   = 0;
    g->hold_used     = 0;
    for (int i = 0; i < NEXT_QUEUE_SIZE; i++) {
        piece_spawn(&g->queue[i], random_type());
    }
    advance_queue(g);
}

void game_run(Game *g) {
    renderer_init();

    ULONGLONG last           = GetTickCount64();
    long      accumulated_ms = 0;

    while (g->state == GAME_RUNNING) {
        ULONGLONG now        = GetTickCount64();
        long      elapsed_ms = (long)(now - last);
        last                 = now;
        accumulated_ms      += elapsed_ms;
        InputKey key = input_poll();
        switch (key) {
            case KEY_QUIT:
                g->state = GAME_OVER;
                break;

            case KEY_LEFT:
                piece_move_left(&g->current, &g->board);
                break;

            case KEY_RIGHT:
                piece_move_right(&g->current, &g->board);
                break;

            case KEY_DOWN:
                if (piece_move_down(&g->current, &g->board))
                    g->score += 1;
                break;

            case KEY_UP:
                piece_rotate(&g->current, &g->board);
                break;

            case KEY_SPACE: {
                int dropped = 0;
                while (piece_move_down(&g->current, &g->board)) dropped++;
                g->score       += dropped * 2;
                accumulated_ms  = g->tick_ms;
                break;
            }

            case KEY_HOLD:
                do_hold(g);
                break;

            default:
                break;
        }
        if (accumulated_ms >= g->tick_ms) {
            accumulated_ms = 0;
            if (!piece_move_down(&g->current, &g->board)) {
                piece_lock(&g->current, &g->board);

                int cleared = board_clear_full_lines(&g->board);
                if (cleared > 0) {
                    g->score         += SCORE_TABLE[cleared] * g->level;
                    g->lines_cleared += cleared;
                    g->level          = g->lines_cleared / 10 + 1;
                    g->tick_ms        = level_speed(g->level);
                }

                advance_queue(g);
            }
        }
        const Piece *hold_ptr = g->hold_active ? &g->hold : NULL;
        renderer_draw(
            &g->board,
            &g->current,
            hold_ptr,
            g->queue,
            NEXT_QUEUE_SIZE,
            g->score,
            g->level,
            g->lines_cleared
        );

        Sleep(16);
    }

    renderer_game_over((unsigned long long)g->score);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}