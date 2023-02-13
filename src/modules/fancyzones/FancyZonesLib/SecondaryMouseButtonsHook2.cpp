#include "pch.h"
#include "SecondaryMouseButtonsHook2.h"
#include <common/debug_control.h>

#pragma region public

HHOOK SecondaryMouseButtonsHook2::hHook = {};
std::function<void(bool)> SecondaryMouseButtonsHook2::callback = {};

SecondaryMouseButtonsHook2::SecondaryMouseButtonsHook2(std::function<void(bool)> extCallback)
{
    callback = std::move(extCallback);
}

void SecondaryMouseButtonsHook2::enable()
{
#if defined(DISABLE_LOWLEVEL_HOOKS_WHEN_DEBUGGED)
    if (IsDebuggerPresent())
    {
        return;
    }
#endif
    if (!hHook)
    {
        hHook = SetWindowsHookEx(WH_MOUSE_LL, SecondaryMouseButtonsProc, GetModuleHandle(NULL), 0);
    }
}

void SecondaryMouseButtonsHook2::disable()
{
    if (hHook)
    {
        UnhookWindowsHookEx(hHook);
        hHook = NULL;
    }
}

#pragma endregion

#pragma region private

LRESULT CALLBACK SecondaryMouseButtonsHook2::SecondaryMouseButtonsProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        if (wParam == WM_XBUTTONDOWN)
        {
            auto mouseStruct = *((MSLLHOOKSTRUCT*)lParam);
            callback(mouseStruct.mouseData & 0x10000);
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

#pragma endregion
