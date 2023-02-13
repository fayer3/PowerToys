#pragma once

#include <functional>

class SecondaryMouseButtonsHook2
{
public:
    SecondaryMouseButtonsHook2(std::function<void(bool)>);
    void enable();
    void disable();

private:
    static HHOOK hHook;
    static std::function<void(bool)> callback;
    static LRESULT CALLBACK SecondaryMouseButtonsProc(int, WPARAM, LPARAM);
};
