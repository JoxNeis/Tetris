#include "renderer/Renderer.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

const char *COLOR_CODES[] = {
    "",         /* 0 = Empty cell                  */
    "\033[96m", /* 1 = Cyan    (I-Piece)            */
    "\033[93m", /* 2 = Yellow  (O-Piece)            */
    "\033[95m", /* 3 = Magenta (T-Piece)            */
    "\033[92m", /* 4 = Green   (S-Piece)            */
    "\033[91m", /* 5 = Red     (Z-Piece)            */
    "\033[94m", /* 6 = Blue    (J-Piece)            */
    "\033[33m", /* 7 = Orange  (L-Piece)            */
    "\033[90m", /* 8 = Grey    (Ghost indicator)    */
};


#ifdef _WIN32
static void enable_ansi_win32(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mode = 0;
    if (hOut != INVALID_HANDLE_VALUE) {
        GetConsoleMode(hOut, &mode);
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        SetConsoleOutputCP(65001);
    }
}
#else
static void enable_ansi_unix(void) {
    /* Linux / macOS – ANSI is enabled by default; nothing to do. */
}
#endif


void enable_ansi(void) {
#ifdef _WIN32
    enable_ansi_win32();
#else
    enable_ansi_unix();
#endif
}

void renderer_clear(void) {
    enable_ansi();
    printf("\033[2J\033[H");
    fflush(stdout);
}

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void render(const char *item, int row, int col) {
    move_cursor(row, col);
    printf("%s", item);
}

void render_flush(void) {
    fflush(stdout);
}