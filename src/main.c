#include "Game.h"
#include "Input.h"
#include "Renderer.h"

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

/* ------------------------------------------------------------------ */
/*  Menu                                                               */
/* ------------------------------------------------------------------ */

typedef enum { MENU_PLAY = 0, MENU_QUIT, MENU_COUNT } MenuItem;

static const char *MENU_LABELS[] = { "Play", "Quit" };

static void draw_menu(MenuItem selected) {
    printf("\033[2J\033[H");
    move_cursor(3, 10);  
    printf("\033[1;96m\n"
       "  _______ ______ _______ _____  _____  _____ \n"
       " |__   __|  ____|__   __|  __ \\|_   _|/ ____|\n"
       "    | |  | |__     | |  | |__) | | | | (___  \n"
       "    | |  |  __|    | |  |  _  /  | |  \\___ \\ \n"
       "    | |  | |____   | |  | | \\ \\ _| |_ ____) |\n"
       "    |_|  |______|  |_|  |_|  \\_\\_____|_____/ \n"
       "\033[0m\n");

    /* Menu items */
    for (int i = 0; i < MENU_COUNT; i++) {
        move_cursor(12 + i * 2, 18);
        if (i == (int)selected) {
            printf("\033[1;93m >> %s << \033[0m", MENU_LABELS[i]);
        } else {
            printf("\033[37m    %s    \033[0m", MENU_LABELS[i]);
        }
    }
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

            case KEY_SPACE:
            case KEY_ENTER:
                return selected;

            case KEY_QUIT:
                return MENU_QUIT;

            default: break;
        }

        Sleep(16);
    }
}


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
                game_run(&g);
                break;
            }
            case MENU_QUIT:
            default:
                running = false;
                break;
        }
    }

    input_cleanup();
    printf("\033[2J\033[H");
    printf("Thanks for playing!\n");

    return 0;
}