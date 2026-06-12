#include "Game.h"
#include "Input.h"
#include "Renderer.h"

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

/* Move cursor to row, col (1-based) */
static void goto_xy(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

static void enable_ansi(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(65001);

    /* Hide cursor */
    CONSOLE_CURSOR_INFO ci = { 1, FALSE };
    SetConsoleCursorInfo(hOut, &ci);
}

/* ------------------------------------------------------------------ */
/*  Menu                                                               */
/* ------------------------------------------------------------------ */

typedef enum { MENU_PLAY = 0, MENU_QUIT, MENU_COUNT } MenuItem;

static const char *MENU_LABELS[] = { "Play", "Quit" };

static void draw_menu(MenuItem selected) {
    printf("\033[2J\033[H"); /* clear screen */

    /* Title */
    goto_xy(3, 10);  printf("\033[1;96m");
    goto_xy(3, 10);  printf("  _____ ____ _____ ____ ___ ____  ");
    goto_xy(4, 10);  printf(" |_   _| ___||_   _|  _ \\|_ _/ ___| ");
    goto_xy(5, 10);  printf("   | | | _|    | | | |_) || |\\___ \\ ");
    goto_xy(6, 10);  printf("   | | | |___  | | |  _ < | | ___) |");
    goto_xy(7, 10);  printf("   |_| |_____| |_| |_| \\_\\___|____/ ");
    printf("\033[0m");

    /* Subtitle */
    goto_xy(9, 16);
    printf("\033[90mUse W/S or arrows to navigate, Enter to select\033[0m");

    /* Menu items */
    for (int i = 0; i < MENU_COUNT; i++) {
        goto_xy(12 + i * 2, 18);
        if (i == (int)selected) {
            printf("\033[1;93m >> %s << \033[0m", MENU_LABELS[i]);
        } else {
            printf("\033[37m    %s    \033[0m", MENU_LABELS[i]);
        }
    }

    /* Controls hint */
    goto_xy(18, 14);
    printf("\033[90mW/Up: Up   S/Down: Down   Enter: Select\033[0m");

    fflush(stdout);
}

static MenuItem run_menu(void) {
    MenuItem selected = MENU_PLAY;

    draw_menu(selected);

    while (true) {
        InputKey key = input_poll();

        switch (key) {
            case KEY_UP:
                selected = (selected == 0) ? MENU_COUNT - 1 : selected - 1;
                draw_menu(selected);
                break;

            case KEY_DOWN:
                selected = (selected + 1) % MENU_COUNT;
                draw_menu(selected);
                break;

            case KEY_SPACE:  /* fall-through: space or enter confirms */
            case KEY_ENTER:
                return selected;

            case KEY_QUIT:
                return MENU_QUIT;

            default: break;
        }

        Sleep(16);
    }
}

/* ------------------------------------------------------------------ */
/*  Entry point                                                        */
/* ------------------------------------------------------------------ */

int main(void) {
    enable_ansi();
    input_init();

    bool running = true;
    while (running) {
        MenuItem choice = run_menu();

        switch (choice) {
            case MENU_PLAY: {
                Game g;
                game_init(&g);
                game_run(&g);   /* blocks until game over */
                break;
            }
            case MENU_QUIT:
            default:
                running = false;
                break;
        }
    }

    input_cleanup();

    /* Clear screen and show goodbye */
    printf("\033[2J\033[H");
    printf("Thanks for playing!\n");

    return 0;
}