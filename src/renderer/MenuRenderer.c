#include "renderer/MenuRenderer.h"
#include "renderer/Renderer.h"
#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define SELECT_COLOR "\033[93m"
#define UNSELECT_COLOR "\033[90m"

static const char *MENU_LAYOUT[] = {
    "┌─────────────────────────────────────────────┐",
    "│                                             │",
    "│   ██████  ██████  ██████  █████   ██  ████  │",
    "│     ██    ██        ██    ██  ██  ██  ██    │",
    "│     ██    ████      ██    █████   ██   ██   │",
    "│     ██    ██        ██    ██  ██  ██    ██  │",
    "│     ██    ██████    ██    ██  ██  ██  ████  │",
    "│                                             │",
    "├─────────────────────────────────────────────┤",
    "│                                             │",
    "│                    PLAY                     │",
    "│                                             │",
    "│                 LEADERBOARD                 │",
    "│                                             │",
    "│                     QUIT                    │",
    "│                                             │",
    "└─────────────────────────────────────────────┘"
};

#define MENU_ROW_COUNT (int)(sizeof(MENU_LAYOUT) / sizeof(MENU_LAYOUT[0]))
#define MENU_START_ROW 4
#define MENU_START_COL 39

static int s_first_render = 1;
static int s_prev_selected_index = -1;

void menu_renderer_init(void) {
    renderer_clear();
    s_first_render = 1;
    s_prev_selected_index = -1;
}

/**
 * @brief Redraws an individual menu option line based on its selection state.
 * @param index Item ID (0 = Play, 1 = Leaderboard, 2 = Quit)
 * @param is_selected True if active highlight needs to be applied
 */
static void draw_menu_option(int index, int is_selected) {
    char option_buf[128];
    int target_row = MENU_START_ROW + 10 + (index * 2);

    if (is_selected) {
        switch (index) {
            case 0:
                snprintf(option_buf, sizeof(option_buf), 
                         "│                " SELECT_COLOR "►  P L A Y  ◄" RESET "                │");
                break;
            case 1:
                snprintf(option_buf, sizeof(option_buf), 
                         "│         " SELECT_COLOR "►  L E A D E R B O A R D  ◄" RESET "         │");
                break;
            case 2:
                snprintf(option_buf, sizeof(option_buf), 
                         "│                " SELECT_COLOR "►  Q U I T  ◄" RESET "                │");
                break;
            default:
                return;
        }
    } else {
        switch (index) {
            case 0:
                snprintf(option_buf, sizeof(option_buf), 
                         "│                   " UNSELECT_COLOR "P L A Y" RESET "                   │");
                break;
            case 1:
                snprintf(option_buf, sizeof(option_buf), 
                         "│              " UNSELECT_COLOR "L E A D E R B O A R D" RESET "          │");
                break;
            case 2:
                snprintf(option_buf, sizeof(option_buf), 
                         "│                   " UNSELECT_COLOR "Q U I T" RESET "                   │");
                break;
            default:
                return;
        }
    }

    render(option_buf, target_row, MENU_START_COL);
}

void menu_renderer_draw(int selected_index) {
    if (s_first_render) {
        for (int i = 0; i < MENU_ROW_COUNT; i++) {
            if (i != 10 && i != 12 && i != 14) {
                render(MENU_LAYOUT[i], MENU_START_ROW + i, MENU_START_COL);
            }
        }
    
        for (int i = 0; i < 3; i++) {
            if (i != selected_index) {
                draw_menu_option(i, 0);
            }
        }
    }

    if (s_first_render || selected_index != s_prev_selected_index) {
        if (s_prev_selected_index >= 0 && s_prev_selected_index < 3) {
            draw_menu_option(s_prev_selected_index, 0);
        }
        if (selected_index >= 0 && selected_index < 3) {
            draw_menu_option(selected_index, 1);
        }

        s_prev_selected_index = selected_index;
    }

    if (s_first_render) {
        s_first_render = 0;
    }

    render_flush();
}