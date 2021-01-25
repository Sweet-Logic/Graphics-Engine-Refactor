#include "Application.h"
#include "Utils/globals.h"
#include <Windows.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	g_cmdShow = nCmdShow;
	g_handleInstance = hInstance;

	g_prevHandelInstance;
	g_cmpCmdLine;

	Application& alias = Application::GetInstance();

	if (FAILED(alias.Initialise(hInstance, nCmdShow)))
	{
		return -1;
	}

    // Main message loop
    MSG msg = {0};
	
	alias.Start();
	
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			alias.Update();
        }
    }

	alias.Release();

    return (int) msg.wParam;
}