#pragma once
#include "pch.h"
#include "framework.h"

#define MAX_LOADSTRING 100

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, int nCmdShow);
	int MessageLoop();
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
	
	LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);

	void ReportMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
	static MainWindow* mainWindow;
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
	HINSTANCE hInst;
	HWND hMainWindow;
	HWND hEdit;
	HWND hInfoEdit; // окно, в котором выводится информация

	// Карта сообщений, которые будут отслеживаться
	std::unordered_map<UINT, std::wstring> observedMessageMap;

	// Флаг, который включает/выключает показ сообщений 
	BOOL IsActive = TRUE;
};

