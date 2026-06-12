#ifndef INPUT_H
#define INPUT_H

typedef enum {
    KEY_NONE  = 0,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_UP,      /* rotate */
    KEY_SPACE,   /* hard drop */
    KEY_ENTER,
    KEY_QUIT
} InputKey;

/* Configure terminal for raw (non-blocking) input */
void input_init(void);
/* Restore terminal to original settings */
void input_cleanup(void);
/* Return the next key without blocking (KEY_NONE if nothing pressed) */
InputKey input_poll(void);

#endif