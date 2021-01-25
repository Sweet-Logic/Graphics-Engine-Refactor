#ifndef _WINDOW_H_
#define _WINDOW_H_
#include "../System.h"
#include <Windows.h>
#include "../../Utils/Maths/Vector2D.h"

class Window : public System<Window>
{
public:
    static Window* s_insance;
    enum E_WINDOW_STATE
    {
        WINDOWED = 0x00,
        FULLSCREEN = 0x01,
        BOARDERLESS_WINDOWED = 0x02
    };

private:
    Vector2 m_windowSize = Vector2(100.f, 100.f);
    Vector2 m_windowPos = Vector2(0.f, 0.f);

    E_WINDOW_STATE m_windowState = E_WINDOW_STATE::WINDOWED;

    HWND m_windowHandle;

public:
    HRESULT Initialise() override;
	void Update() override {};
    void Release() override;

    double GetWidth() { return m_windowSize.x; }
	double GetHight() { return m_windowSize.y; }
    void SetWidth(float width) { m_windowSize.x = width; }
    void SetHeight(float height) { m_windowSize.y = height; }

	void RedrawWindow() {};


    HWND GetWindowHandle() { return m_windowHandle; }
    static LRESULT CALLBACK WndRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif