#include "Renderer.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

/* ANSI color codes indexed by piece color value (1-7) */
static const char *COLOR_CODES[] = {
    "",         /* 0 = empty       */
    "\033[96m", /* 1 = Cyan    (I) */
    "\033[93m", /* 2 = Yellow  (O) */
    "\033[95m", /* 3 = Magenta (T) */
    "\033[92m", /* 4 = Green   (S) */
    "\033[91m", /* 5 = Red     (Z) */
    "\033[94m", /* 6 = Blue    (J) */
    "\033[33m", /* 7 = Orange  (L) */
};
#define GREY_TEXT "\033[90m"
#define RESET "\033[0m"
#define BLOCK "[]"
#define GHOST "{}"
#define EMPTY "  "

/* Move cursor to row, col (1-based) */
static void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

/* Enable ANSI escape processing on Windows 10+ */
static void enable_ansi(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    /* Set console output to UTF-8 (code page 65001) */
    SetConsoleOutputCP(65001);
}

void renderer_clear(void) {
    enable_ansi();
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* Print a fixed-width side panel line, padding with spaces to clear old text */
#define PANEL_WIDTH 20
static void print_panel(int board_row, const char *text) {
    /* Side panel starts at column: border(1) + board(20 cols * 2 chars) + border(1) + space(2) = 25 */
    move_cursor(board_row + 1, 25); /* +1 because top border is row 1 */
    printf("%-*s", PANEL_WIDTH, text); /* left-align, pad to PANEL_WIDTH */
}

void renderer_draw(const Board *b, const Piece *current,
                   int score, int level, int lines) {
    /* Build overlay grid */
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
    memcpy(grid, b->cells, sizeof(grid));

    /* Ghost piece */
    Piece ghost = *current;
    while (piece_move_down(&ghost, b)) {}
    int ghost_shape[4][4];
    piece_get_shape(&ghost, ghost_shape);

    /* Active piece */
    int shape[4][4];
    piece_get_shape(current, shape);
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (shape[r][c]) {
                int br = current->row + r, bc = current->col + c;
                if (br >= 0 && br < BOARD_HEIGHT && bc >= 0 && bc < BOARD_WIDTH)
                    grid[br][bc] = current->tetromino->color;
            }

    /* Draw from top-left every frame */
    move_cursor(1, 1);

    /* Top border */
    printf("+");
    for (int c = 0; c < BOARD_WIDTH; c++) printf("--");
    printf("+");

    /* Score on same line as top border */
    printf("  Score : %d      ", score);
    printf("\n");

    for (int r = 0; r < BOARD_HEIGHT; r++) {
        printf("|");
        for (int c = 0; c < BOARD_WIDTH; c++) {
            int cell = grid[r][c];
            if (cell) {
                printf("%s%s%s", COLOR_CODES[cell], BLOCK, RESET);
            } else {
                /* Ghost? */
                int is_ghost = 0;
                for (int gr = 0; gr < 4 && !is_ghost; gr++)
                    for (int gc = 0; gc < 4 && !is_ghost; gc++)
                        if (ghost_shape[gr][gc] &&
                            ghost.row + gr == r &&
                            ghost.col + gc == c)
                            is_ghost = 1;
                printf("%s%s%s", GREY_TEXT,is_ghost ? GHOST : EMPTY, RESET);
            }
        }
        printf("|");
        printf("\n");
    }

    /* Bottom border */
    printf("+");
    for (int c = 0; c < BOARD_WIDTH; c++) printf("--");
    printf("+\n");

    /* Side panel — printed with fixed positions to avoid ghosting */
    char buf[32];

    print_panel(2,  "");
    snprintf(buf, sizeof(buf), "Level : %d", level);
    print_panel(3,  buf);
    print_panel(4,  "");
    snprintf(buf, sizeof(buf), "Lines : %d", lines);
    print_panel(5,  buf);
    print_panel(6,  "");
    print_panel(7,  "Controls:");
    print_panel(8,  "Arrow/WASD: Move");
    print_panel(9,  "Up/W : Rotate");
    print_panel(10, "Down/S : Soft drop");
    print_panel(11, "Space : Hard drop");
    print_panel(12, "Q : Quit");

    fflush(stdout);
}

void renderer_game_over(int score) {
    move_cursor(23, 1);
    printf("\n  GAME OVER\n");
    printf("  Final score: %d\n", score);
    printf("  Press Enter to exit...\n");
    fflush(stdout);
}