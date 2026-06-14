#include "renderer/GameRenderer.h"
#include "renderer/Renderer.h"
#include "Board.h"
#include "Piece.h"
#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define BLOCK "[]"
#define EMPTY "  "

static const char *SIDEBAR_LAYOUT[] = {
    "┌──────────────────────────────────┐",
    "│         - T E T R I S -          │",
    "├──────────────────────────────────┤",
    "│  SCORE:  00000000                │",
    "│  LEVEL:  00                      │",
    "│  LINES:  000                     │",
    "├──────────────────────────────────┤",
    "│  CONTROLS:                       │",
    "│  W / Up     : Rotate             │",
    "│  A/D / Left : Move Left/Right    │",
    "│  S / Down   : Soft Drop          │",
    "│  Space      : Hard Drop          │",
    "│  Q          : Hold Piece         │",
    "│  Esc        : Quit Game          │",
    "└──────────────────────────────────┘"
};

static const char *HOLD_PIECE_LAYOUT[] = {
    "┌──────────────────────────────────┐",
    "│         - - H O L D - -          │",
    "├──────────────────────────────────┤",
    "│                                  │",
    "│                                  │",
    "│                                  │",
    "│                                  │",
    "└──────────────────────────────────┘"
};

static const char *QUEUE_PICE_LAYOUT[] = {
    "┌──────────────────────────────────┐",
    "│    - Q U E U E - P I E C E S -   │",
    "├──────────────────────────────────┤",
    "│  Next:                           │",
    "│                                  │",
    "│                                  │",
    "├──────────────────────────────────┤",
    "│                                  │",
    "│                                  │",
    "├──────────────────────────────────┤",
    "│                                  │",
    "│                                  │",
    "├──────────────────────────────────┤",
    "│                                  │",
    "│                                  │",
    "├──────────────────────────────────┤",
    "│                                  │",
    "│                                  │",
    "└──────────────────────────────────┘"
};

#define SIDEBAR_ROW_COUNT (int)(sizeof(SIDEBAR_LAYOUT) / sizeof(SIDEBAR_LAYOUT[0]))
static int s_first_render = 1;
static int s_prev_grid[BOARD_HEIGHT][BOARD_WIDTH];
static int s_prev_score = -1;
static int s_prev_level = -1;
static int s_prev_lines = -1;
static int s_prev_hold_color = -1;
static int s_prev_next_colors[5] = {-1, -1, -1, -1, -1};

void renderer_init(void) {
    renderer_clear();
    s_first_render = 1;
    s_prev_score = -1;
    s_prev_level = -1;
    s_prev_lines = -1;
    s_prev_hold_color = -1;
    for (int i = 0; i < 5; i++) {
        s_prev_next_colors[i] = -1;
    }
    memset(s_prev_grid, -1, sizeof(s_prev_grid));
}

/**
 * @brief Renders the static borders and internal dynamic modifications of the play field.
 */
static void render_game_board(const int grid[BOARD_HEIGHT][BOARD_WIDTH]) {
    int board_x = 39;
    if (s_first_render) {
        char border_buf[128];
        int pos = 0;

        pos = snprintf(border_buf, sizeof(border_buf), "┌");
        for (int c = 0; c < BOARD_WIDTH; c++) {
            pos += snprintf(border_buf + pos, sizeof(border_buf) - pos, "──");
        }
        snprintf(border_buf + pos, sizeof(border_buf) - pos, "┐");
        render(border_buf, 1, board_x);

        for (int r = 0; r < BOARD_HEIGHT; r++) {
            render("│", r + 2, board_x);
            render("│", r + 2, board_x + 1 + (BOARD_WIDTH * 2));
        }

        pos = snprintf(border_buf, sizeof(border_buf), "└");
        for (int c = 0; c < BOARD_WIDTH; c++) {
            pos += snprintf(border_buf + pos, sizeof(border_buf) - pos, "──");
        }
        snprintf(border_buf + pos, sizeof(border_buf) - pos, "┘");
        render(border_buf, BOARD_HEIGHT + 2, board_x);
    }

    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {
            int current_cell = grid[r][c];
            if (s_first_render || s_prev_grid[r][c] != current_cell) {
                char cell_str[64];
                if (current_cell > 0) {
                    snprintf(cell_str, sizeof(cell_str), "%s%s%s", COLOR_CODES[current_cell], BLOCK, RESET);
                } else {
                    snprintf(cell_str, sizeof(cell_str), "%s", EMPTY);
                }
                render(cell_str, r + 2, board_x + 1 + (c * 2));
                s_prev_grid[r][c] = current_cell;
            }
        }
    }
}

/**
 * @brief Dynamically renders held piece state and scales shapes perfectly.
 */
static void render_hold_panel(const Piece *hold) {
    int hold_x = 1; // Left side of Matrix
    if (s_first_render) {
        for (int i = 0; i < 8; i++) {
            render(HOLD_PIECE_LAYOUT[i], i + 1, hold_x);
        }
    }

    int hold_color = (hold && hold->tetromino) ? hold->tetromino->color : 0;
    if (s_first_render || hold_color != s_prev_hold_color) {
        for (int r = 4; r <= 7; r++) {
            render("│                                  │", r, hold_x);
        }

        if (hold && hold->tetromino) {
            int shape[4][4];
            piece_get_shape(hold, shape);
            int min_r = 4, max_r = -1, min_c = 4, max_c = -1;
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    if (shape[r][c]) {
                        if (r < min_r) min_r = r;
                        if (r > max_r) max_r = r;
                        if (c < min_c) min_c = c;
                        if (c > max_c) max_c = c;
                    }
                }
            }

            if (max_r != -1) {
                int w = max_c - min_c + 1;
                int start_c = hold_x + 18 - w;
                for (int r = min_r; r <= max_r; r++) {
                    for (int c = min_c; c <= max_c; c++) {
                        if (shape[r][c]) {
                            char cell_str[64];
                            snprintf(cell_str, sizeof(cell_str), "%s%s%s", COLOR_CODES[hold_color], BLOCK, RESET);
                            render(cell_str, 4 + (r - min_r), start_c + (c - min_c) * 2);
                        }
                    }
                }
            }
        }
        s_prev_hold_color = hold_color;
    }
}

/**
 * @brief Dynamically updates next pieces inside queue layout slots.
 */
static void render_queue_panel(const Piece *next_pieces, int next_count) {
    int queue_x = 64;
    if (s_first_render) {
        for (int i = 0; i < 19; i++) {
            render(QUEUE_PICE_LAYOUT[i], i + 1, queue_x);
        }
    }

    int next_colors[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++) {
        if (next_pieces && i < next_count && next_pieces[i].tetromino) {
            next_colors[i] = next_pieces[i].tetromino->color;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (s_first_render || next_colors[i] != s_prev_next_colors[i]) {
            int start_row = 5 + (i * 3);
            render("│                                  │", start_row, queue_x);
            render("│                                  │", start_row + 1, queue_x);

            if (next_pieces && i < next_count && next_pieces[i].tetromino) {
                int shape[4][4];
                piece_get_shape(&next_pieces[i], shape);

                int min_r = 4, max_r = -1, min_c = 4, max_c = -1;
                for (int r = 0; r < 4; r++) {
                    for (int c = 0; c < 4; c++) {
                        if (shape[r][c]) {
                            if (r < min_r) min_r = r;
                            if (r > max_r) max_r = r;
                            if (c < min_c) min_c = c;
                            if (c > max_c) max_c = c;
                        }
                    }
                }

                if (max_r != -1) {
                    int w = max_c - min_c + 1;
                    int start_c = queue_x + 18 - w;
                    for (int r = min_r; r <= max_r; r++) {
                        for (int c = min_c; c <= max_c; c++) {
                            if (shape[r][c]) {
                                char cell_str[64];
                                snprintf(cell_str, sizeof(cell_str), "%s%s%s", COLOR_CODES[next_colors[i]], BLOCK, RESET);
                                render(cell_str, start_row + (r - min_r), start_c + (c - min_c) * 2);
                            }
                        }
                    }
                }
            }
            s_prev_next_colors[i] = next_colors[i];
        }
    }
}

/**
 * @brief Renders the side stats panel stacked cleanly underneath the Queue list.
 */
static void render_game_ui(int score, int level, int lines) {
    int ui_x = 64;
    int ui_y_offset = 20;
    if (s_first_render) {
        for (int i = 0; i < SIDEBAR_ROW_COUNT; i++) {
            if (i != 3 && i != 4 && i != 5) {
                render(SIDEBAR_LAYOUT[i], ui_y_offset + i + 1, ui_x);
            }
        }
    }

    char item_buf[128];
    if (s_first_render || score != s_prev_score) {
        snprintf(item_buf, sizeof(item_buf), "│  SCORE:  %08d                │", score);
        render(item_buf, ui_y_offset + 4, ui_x);
        s_prev_score = score;
    }
    if (s_first_render || level != s_prev_level) {
        snprintf(item_buf, sizeof(item_buf), "│  LEVEL:  %02d                      │", level);
        render(item_buf, ui_y_offset + 5, ui_x);
        s_prev_level = level;
    }
    if (s_first_render || lines != s_prev_lines) {
        snprintf(item_buf, sizeof(item_buf), "│  LINES:  %03d                     │", lines);
        render(item_buf, ui_y_offset + 6, ui_x);
        s_prev_lines = lines;
    }
}

void renderer_draw(const Board *b, const Piece *current, const Piece *hold, 
                   const Piece *next_pieces, int next_count, 
                   int score, int level, int lines) {
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
    memcpy(grid, b->cells, sizeof(grid));

    Piece ghost = *current;
    while (piece_move_down(&ghost, b)) {}
    
    int ghost_shape[4][4];
    piece_get_shape(&ghost, ghost_shape);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (ghost_shape[r][c]) {
                int br = ghost.row + r, bc = ghost.col + c;
                if (br >= 0 && br < BOARD_HEIGHT && bc >= 0 && bc < BOARD_WIDTH) {
                    grid[br][bc] = 8;
                }
            }
        }
    }

    int shape[4][4];
    piece_get_shape(current, shape);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (shape[r][c]) {
                int br = current->row + r, bc = current->col + c;
                if (br >= 0 && br < BOARD_HEIGHT && bc >= 0 && bc < BOARD_WIDTH) {
                    grid[br][bc] = current->tetromino->color;
                }
            }
        }
    }
    render_game_board(grid);
    render_hold_panel(hold);
    render_queue_panel(next_pieces, next_count);
    render_game_ui(score, level, lines);

    if (s_first_render) {
        s_first_render = 0;
    }
    render_flush();
}

void renderer_game_over(unsigned long long score) {
    move_cursor(BOARD_HEIGHT + 4, 1);
    printf("\n");
    printf("┌──────────────────────────┐\n");
    printf("│      G A M E   O V E R   │\n");
    printf("├──────────────────────────┤\n");
    printf("│  Final Score: %-10llu │\n", score);
    printf("│  Press Enter to exit...  │\n");
    printf("└──────────────────────────┘\n\n");
    render_flush();
}