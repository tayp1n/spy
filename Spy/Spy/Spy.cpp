// Spy.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "MainWindow.h"

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    MainWindow mainWindow(hInstance, nCmdShow);
    return mainWindow.MessageLoop();    
}
