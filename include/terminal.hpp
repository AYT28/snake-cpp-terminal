#pragma once
#include <windows.h>

class Terminal {
    private:
    HANDLE outputHandle;
    HANDLE inputHandle;

    public:
    Terminal();

    void resetCursor();
    void setCursorVisibility(bool visible);
    void setUTF8();
    void getSize(int& width, int& height);

    bool keyPressed();
    char getKey();
};