#include "Game.h"
#include "Input.h"
#include "renderer/MenuRenderer.h"
#include "renderer/Renderer.h"

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

typedef enum {
    MENU_PLAY        = 0,
    MENU_LEADERBOARD = 1,
    MENU_QUIT        = 2,
    MENU_COUNT       = 3
} MenuItem;

static MenuItem run_menu(void) {
    MenuItem selected = MENU_PLAY;

    menu_renderer_init();
    menu_renderer_draw((int)selected);

    while (true) {
        InputKey key = input_poll();

        switch (key) {
            case KEY_UP:
                selected = (selected == 0)
                    ? (MenuItem)(MENU_COUNT - 1)
                    : (MenuItem)(selected - 1);
                menu_renderer_draw((int)selected);
                break;

            case KEY_DOWN:
                selected = (MenuItem)((selected + 1) % MENU_COUNT);
                menu_renderer_draw((int)selected);
                break;

            case KEY_SPACE:
            case KEY_ENTER:
                return selected;

            case KEY_QUIT:
                return MENU_QUIT;

            default:
                break;
        }

        Sleep(16);
    }
}

static void run_leaderboard(void) {
    renderer_clear();
    move_cursor(5, 10);
    printf("\033[1;93m[ LEADERBOARD - Coming Soon ]\033[0m\n");
    move_cursor(7, 10);
    printf("Press any key to return to the menu...");
    render_flush();
    while (input_poll() != KEY_NONE) Sleep(16);
    while (input_poll() == KEY_NONE) Sleep(16);
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

            case MENU_LEADERBOARD:
                run_leaderboard();
                break;

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