#include "ccmds.h"
#include <Windows.h>

void console::set_cursor_pos(short x, short y)
{
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), dwPos);
}

std::vector<int> console::get_size()
{
    HWND hWnd = GetConsoleWindow();
    RECT rect; std::vector<int> size;
    if (GetWindowRect(hWnd, &rect))
    {
        size.push_back(rect.right - rect.left);
        size.push_back(rect.bottom - rect.top);
        return size;
    }
    size.push_back(-1);
    return size;
}