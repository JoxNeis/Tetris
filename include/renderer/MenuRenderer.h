#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

/**
 * @file MenuRenderer.h
 * @brief High-performance main menu rendering engine for Tetris, featuring
 * double-buffered option selection, box-drawing styling, and zero-flicker transitions.
 */

/**
 * @brief Fully clears the terminal screen, resets dirty indexing states, 
 * and draws the static menu containers.
 */
void menu_renderer_init(void);

/**
 * @brief Evaluates menu state changes and performs delta updates on option highlighting.
 * @param selected_index The currently active menu selection (0 = Play, 1 = Leaderboard, 2 = Quit).
 */
void menu_renderer_draw(int selected_index);

#endif /* MENU_RENDERER_H */