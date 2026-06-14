#ifndef INPUT_H
#define INPUT_H

/**
 * @file Input.h
 * @brief Input handling definitions for key mappings, including action types,
 * device setup, and frame-by-frame keyboard state polling.
 */

/**
 * @brief Input actions recognized by the Tetris engine.
 */
typedef enum {
    KEY_NONE  = 0,  /**< No key pressed or unrecognized key */
    KEY_LEFT,       /**< Move block left (Arrow Left / A) */
    KEY_RIGHT,      /**< Move block right (Arrow Right / D) */
    KEY_DOWN,       /**< Soft drop block (Arrow Down / S) */
    KEY_UP,         /**< Rotate block (Arrow Up / W) */
    KEY_SPACE,      /**< Hard drop block */
    KEY_ENTER,      /**< Interface select / confirmation */
    KEY_HOLD,       /**< Hold current block swap action (Q) */
    KEY_QUIT        /**< Terminate current game session (Escape) */
} InputKey;

/**
 * @brief Prepares console input processing (e.g. hiding the terminal cursor).
 */
void input_init(void);

/**
 * @brief Restores console input settings to default system states upon game teardown.
 */
void input_cleanup(void);

/**
 * @brief Polls the input buffer in a non-blocking manner to read the latest keyboard input state.
 * @return The mapped InputKey corresponding to the pressed key, or KEY_NONE if no key is active.
 */
InputKey input_poll(void);

#endif /* INPUT_H */