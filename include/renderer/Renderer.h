#ifndef RENDERER_H
#define RENDERER_H

/**
 * @file Renderer.h
 * @brief Core terminal rendering engine for managing ANSI console cursor offsets, 
 * rendering UTF-8 box styling, handling Windows virtual terminal initialization, and flush streams.
 */

/* Color ANSI codes map used for tetrominos and system components */
extern const char *COLOR_CODES[];

/**
 * @brief Enables ANSI virtual terminal processing sequence on Windows terminals.
 * Also configures the system standard output to handle UTF-8 symbols (CP 65001)
 * to ensure that box-drawing lines and control symbols display correctly.
 */
void enable_ansi(void);

/**
 * @brief Clear the console workspace completely and resets standard cursors to top-left (1,1).
 */
void renderer_clear(void);

/**
 * @brief Shifts terminal cursor coordinates using ANSI escape parameters.
 * @param row 1-based target row.
 * @param col 1-based target column.
 */
void move_cursor(int row, int col);

/**
 * @brief Prints an item directly onto specified terminal coordinates.
 * @param item Null-terminated visual string containing formatting or raw text.
 * @param row 1-based target row.
 * @param col 1-based target column.
 */
void render(const char *item, int row, int col);

/**
 * @brief Flushes standard stdout stream to prevent partial rendering and ensure consistent updates.
 */
void render_flush(void);

#endif /* RENDERER_H */