#pragma once

#include <FancyZonesLib/KeyState.h>
#include <FancyZonesLib/SecondaryMouseButtonsHook.h>
#include <FancyZonesLib/SecondaryMouseButtonsHook2.h>

class DraggingState
{
public:
    DraggingState(const std::function<void()>& keyUpdateCallback);
    ~DraggingState() = default;

    void Enable();
    void Disable();
    void UpdateDraggingState() noexcept;

    bool IsDragging() const noexcept;
    bool IsSelectManyZonesState() const noexcept;
    int DraggingState::CurrentLayoutState() noexcept;

private:
    void OnMouseDown();
    void OnMouseDown2(bool a);

    std::atomic<bool> m_mouseState;
    std::atomic<int> m_mouseState2;
    std::atomic<int> m_mouseState2New;
    SecondaryMouseButtonsHook m_mouseHook;
    SecondaryMouseButtonsHook2 m_mouseHook2;
    KeyState<VK_LSHIFT> m_leftShiftKeyState;
    KeyState<VK_RSHIFT> m_rightShiftKeyState;
    KeyState<VK_LCONTROL, VK_RCONTROL> m_ctrlKeyState;
    std::function<void()> m_keyUpdateCallback;

    bool m_dragging{}; // True if we should be showing zone hints while dragging
};
