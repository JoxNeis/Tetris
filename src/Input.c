#include "Input.h"
#include <conio.h>
#include <windows.h>

void input_init(void) {
    /* Hide the cursor for cleaner rendering */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void input_cleanup(void) {
    /* Restore cursor visibility on exit */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

InputKey input_poll(void) {
    if (!_kbhit()) return KEY_NONE;

    int ch = _getch();

    /* Arrow keys return 0 or 224 as first byte, then a code */
    if (ch == 0 || ch == 224) {
        int ch2 = _getch();
        switch (ch2) {
            case 72: return KEY_UP;    /* up arrow    */
            case 80: return KEY_DOWN;  /* down arrow  */
            case 75: return KEY_LEFT;  /* left arrow  */
            case 77: return KEY_RIGHT; /* right arrow */
        }
        return KEY_NONE;
    }

    switch (ch) {
        case '\r':
        case '\n':
            return KEY_ENTER;

        case 'q':
        case 'Q':
            return KEY_QUIT;

        case ' ':
            return KEY_SPACE;

        case 'a':
        case 'A':
            return KEY_LEFT;

        case 'd':
        case 'D':
            return KEY_RIGHT;

        case 's':
        case 'S':
            return KEY_DOWN;

        case 'w':
        case 'W':
            return KEY_UP;

        default:
            return KEY_NONE;
    }
}