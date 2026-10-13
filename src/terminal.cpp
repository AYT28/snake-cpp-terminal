#include "terminal.hpp"

Terminal::Terminal() {
    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    inputHandle = GetStdHandle(STD_INPUT_HANDLE);

    DWORD mode;
    GetConsoleMode(inputHandle, &mode);

    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(inputHandle, mode);

    DWORD outMode;
    GetConsoleMode(outputHandle, &outMode);
    SetConsoleMode(outputHandle, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void Terminal::resetCursor() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(outputHandle, coord);
}

void Terminal::setCursorVisibility(bool visible) {
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(outputHandle, &info);
    info.bVisible = visible;
    SetConsoleCursorInfo(outputHandle, &info);
}

void Terminal::setUTF8() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void Terminal::getSize(int& width, int& height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(outputHandle, &csbi);

    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

bool Terminal::keyPressed() {
    DWORD numberOfEvents;

    GetNumberOfConsoleInputEvents(inputHandle, &numberOfEvents);
    return numberOfEvents > 0;
}

char Terminal::getKey() {
    INPUT_RECORD record;
    DWORD eventsRead;

    ReadConsoleInput(inputHandle, &record, 1, &eventsRead);

    if (record.EventType == KEY_EVENT) {
        KEY_EVENT_RECORD key = record.Event.KeyEvent;

        if (key.bKeyDown) {
            return key.uChar.AsciiChar;
        }
    }

    return '\0';
}