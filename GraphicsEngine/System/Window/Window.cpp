#include "Window.h"
#include "../../Utils/Globals.h"
#include "../../resource.h"

HRESULT Window::Initialise()
{
    // Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndRouter; // <----- Application::s_instance->WinProc ???
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_handleInstance; // <-------- Application::s_instance->hInstance;
	wcex.hIcon = LoadIcon(g_handleInstance, (LPCTSTR)IDI_TUTORIAL1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"TutorialWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	RECT rc = { 0, 0, 1280, 720 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_windowHandle = CreateWindow(L"TutorialWindowClass", L"DX11 Framework", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, g_handleInstance,
		this);

	if (!m_windowHandle)
		return E_FAIL;

	ShowWindow(m_windowHandle, g_cmdShow); // <-------- Application::s_instance->mCmdShow


	GetClientRect(m_windowHandle, &rc);
	m_windowSize.x = rc.right - rc.left;
	m_windowSize.y = rc.bottom - rc.top;

	return S_OK;
}

void Window::Release()
{
	
}

LRESULT CALLBACK Window::WndRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* app;
	if(message == WM_CREATE)
	{
		app = (Window*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)app);
	}
	else
	{
		app = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	return app->WndProc(hWnd, message, wParam, lParam);
}


LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int i = 0;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}