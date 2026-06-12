#include "Game.h"
#include "Input.h"
#include "Renderer.h"

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

static void spawn_next(Game *g) {
    g->current = g->next;
    piece_spawn(&g->next, random_type());
    if (!piece_is_valid(&g->current, &g->board))
        g->state = GAME_OVER;
}

void game_init(Game *g) {
    srand((unsigned)time(NULL));
    board_init(&g->board);

    g->state         = GAME_RUNNING;
    g->score         = 0;
    g->level         = 1;
    g->lines_cleared = 0;
    g->tick_ms       = level_speed(1);

    piece_spawn(&g->next, random_type());
    spawn_next(g);
}

void game_run(Game *g) {
    input_init();
    renderer_clear();

    ULONGLONG last = GetTickCount64();
    long accumulated_ms = 0;

    while (g->state == GAME_RUNNING) {
        /* ---- timing ---- */
        ULONGLONG now = GetTickCount64();
        long elapsed_ms = (long)(now - last);
        last = now;
        accumulated_ms += elapsed_ms;

        /* ---- input ---- */
        InputKey key = input_poll();
        switch (key) {
            case KEY_QUIT:  g->state = GAME_OVER; break;
            case KEY_LEFT:  piece_move_left (&g->current, &g->board); break;
            case KEY_RIGHT: piece_move_right(&g->current, &g->board); break;
            case KEY_DOWN:
                if (piece_move_down(&g->current, &g->board))
                    g->score += 1;
                break;
            case KEY_UP: piece_rotate(&g->current, &g->board); break;
            case KEY_SPACE: {
                int dropped = 0;
                while (piece_move_down(&g->current, &g->board)) dropped++;
                g->score += dropped * 2;
                accumulated_ms = g->tick_ms;
                break;
            }
            default: break;
        }

        /* ---- gravity tick ---- */
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
                spawn_next(g);
            }
        }

        /* ---- render ---- */
        renderer_draw(&g->board, &g->current,
                      g->score, g->level, g->lines_cleared);

        Sleep(16); /* ~60 fps */
    }

    input_cleanup();
    renderer_game_over(g->score);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}