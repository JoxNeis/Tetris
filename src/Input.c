#include "Input.h"
#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

void input_init(void) {
    #ifdef _WIN32
        input_init_win32();
    #else
        input_init_unknown();
    #endif
}

void input_cleanup(void) {
    #ifdef _WIN32
        input_cleanup_win32();
    #else
        input_init_cleanup();
    #endif
}

InputKey input_poll(void) {
    #ifdef _WIN32
        return input_poll_win32();
    #else
        return input_poll_unknown();
    #endif
}

#pragma region WIN32
static input_init_win32(void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

}

static input_cleanup_win32(void){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

static InputKey input_poll_win32(void){
    if (!_kbhit()) {
        return KEY_NONE;
    }
    
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        int ch2 = _getch();
        switch (ch2) {
            case 72: return KEY_UP;
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
            default: return KEY_NONE;
        }
    }
    switch (ch) {
        case 27:
            return KEY_QUIT;

        case 'q':
        case 'Q':
            return KEY_HOLD;

        case ' ':
            return KEY_SPACE;

        case '\r':
        case '\n':
            return KEY_ENTER;

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
#pragma endregion

#pragma region UNKNOWN OS
static void input_init_unknown(void){
    printf("\033[?25l");
    fflush(stdout);
}

static void input_cleanup_unknown(void){
    printf("\033[?25h");
    fflush(stdout);
}

static InputKey input_poll_unknown(void){
    return KEY_NONE;
}
#pragma endregion