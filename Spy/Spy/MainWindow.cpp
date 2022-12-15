#include "pch.h"
#include "MainWindow.h"
#include "resource.h"

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

MainWindow* MainWindow::mainWindow = nullptr;

// Конструктор
MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
{
    mainWindow = this;

    // Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SPY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        throw std::runtime_error("Window creation failed.");
    }

    // Создать карту событий, которые будут отслеживаться

    // События от меню и дочерних окон
    observedMessageMap.insert(std::make_pair(WM_COMMAND, L"WM_COMMAND"));
    observedMessageMap.insert(std::make_pair(WM_NOTIFY, L"WM_NOTIFY"));

    // События от мыши
    observedMessageMap.insert(std::make_pair(WM_MOUSEMOVE, L"WM_MOUSEMOVE"));
    observedMessageMap.insert(std::make_pair(WM_MOUSEWHEEL, L"WM_MOUSEWHEEL"));
    observedMessageMap.insert(std::make_pair(WM_MOUSEACTIVATE, L"WM_MOUSEACTIVATE"));
    observedMessageMap.insert(std::make_pair(WM_MOUSEHOVER, L"WM_MOUSEHOVER"));
    observedMessageMap.insert(std::make_pair(WM_MOUSELEAVE, L"WM_MOUSELEAVE"));

    observedMessageMap.insert(std::make_pair(WM_LBUTTONDOWN, L"WM_LBUTTONDOWN"));
    observedMessageMap.insert(std::make_pair(WM_LBUTTONUP, L"WM_LBUTTONUP"));    
    observedMessageMap.insert(std::make_pair(WM_LBUTTONDBLCLK, L"WM_LBUTTONDBLCLK"));

    observedMessageMap.insert(std::make_pair(WM_RBUTTONDOWN, L"WM_RBUTTONDOWN"));
    observedMessageMap.insert(std::make_pair(WM_RBUTTONUP, L"WM_RBUTTONUP"));
    observedMessageMap.insert(std::make_pair(WM_RBUTTONDBLCLK, L"WM_RBUTTONDBLCLK"));

    observedMessageMap.insert(std::make_pair(WM_MBUTTONDOWN, L"WM_MBUTTONDOWN"));
    observedMessageMap.insert(std::make_pair(WM_MBUTTONUP, L"WM_MBUTTONUP"));
    observedMessageMap.insert(std::make_pair(WM_MBUTTONDBLCLK, L"WM_MBUTTONDBLCLK"));  

    // События от клавиатуры
    observedMessageMap.insert(std::make_pair(WM_ACTIVATE, L"WM_ACTIVATE"));
    observedMessageMap.insert(std::make_pair(WM_CHAR, L"WM_CHAR"));
    observedMessageMap.insert(std::make_pair(WM_DEADCHAR, L"WM_DEADCHAR"));
    observedMessageMap.insert(std::make_pair(WM_HOTKEY, L"WM_HOTKEY"));
    observedMessageMap.insert(std::make_pair(WM_KEYDOWN, L"WM_KEYDOWN"));
    observedMessageMap.insert(std::make_pair(WM_KEYUP, L"WM_KEYUP"));
    observedMessageMap.insert(std::make_pair(WM_KILLFOCUS, L"WM_KILLFOCUS"));
    observedMessageMap.insert(std::make_pair(WM_SETFOCUS, L"WM_SETFOCUS"));
    observedMessageMap.insert(std::make_pair(WM_SYSDEADCHAR, L"WM_SYSDEADCHAR"));
    observedMessageMap.insert(std::make_pair(WM_SYSKEYDOWN, L"WM_SYSKEYDOWN"));
    observedMessageMap.insert(std::make_pair(WM_SYSKEYUP, L"WM_SYSKEYUP"));
    observedMessageMap.insert(std::make_pair(WM_UNICHAR, L"WM_UNICHAR"));
}

// Цикл обработки событий
int MainWindow::MessageLoop()
{
    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_SPY)); 
    
    MSG msg;
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

// Зарегистрировать класс главного окна
ATOM MainWindow::MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SPY);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// Инициализация главного окна
BOOL MainWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    hMainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hMainWindow)
    {
        return FALSE;
    }

    // Создать окно для редактирования
    hEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hMainWindow, nullptr, hInstance, nullptr);

    // Создать окно для вывода информации о сообщении
    hInfoEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_DISABLED | WS_BORDER | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hMainWindow, nullptr, hInstance, nullptr);

    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);    

    return TRUE;
}

// Оконная процедура
LRESULT MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Проверить что это сообщение не от hInfoEdit (иначе возникнет рекурсия)
    if (message != WM_COMMAND || lParam != (LPARAM)mainWindow->hInfoEdit)
    {
        // Если это сообщение есть в карте событий, тогда вывести информацию о сообщении
        if (mainWindow->observedMessageMap.count(message) > 0 && mainWindow->IsActive)
        {
            mainWindow->ReportMessage(message, wParam, lParam);
        }
    }

    switch (message)
    {
    case WM_COMMAND:    
        // Обработка меню
        return mainWindow->OnCommand(hWnd, wParam, lParam);
        break;

    case WM_SIZE:
        // При изменении размера окна
        mainWindow->OnSize(hWnd, wParam, lParam);
        break;

    case WM_DESTROY:
        // При закрытии окна
        mainWindow->OnDestroy(hWnd, wParam, lParam);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработка меню
LRESULT MainWindow::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    UINT state;

    // Parse the menu selections:
    switch (wmId)
    {
    case ID_FILE_CAPTUREEVENTS: // Меню File/Capture Events (Alt+F+C)
        IsActive = !IsActive;
        state = IsActive ? MF_CHECKED : MF_UNCHECKED;
        CheckMenuItem(GetMenu(hWnd), ID_FILE_CAPTUREEVENTS, MF_BYCOMMAND | state);
        break;
    case IDM_ABOUT: // Меню Help/About
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), mainWindow->hMainWindow, About);
        break;
    case IDM_EXIT: // Меню File/Exit
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, WM_COMMAND, wParam, lParam);
    }
}

// При изменении размера главного окна изменить размер дочерних окон
void MainWindow::OnSize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    GetClientRect(hMainWindow, &rc);

    MoveWindow(hEdit, rc.left + (rc.right - rc.left) / 4, rc.top + (rc.bottom - rc.top) / 8, (rc.right - rc.left) / 2, (rc.bottom - rc.top) / 4, 1);

    MoveWindow(hInfoEdit, rc.left, rc.top + (rc.bottom - rc.top) / 2, rc.right - rc.left, (rc.bottom - rc.top) / 2, 1);
}

// Послать сообщение PostQuitMessage при закрытии окна
void MainWindow::OnDestroy(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    PostQuitMessage(0);
}

// Вывести информацию о сообщении в элемент редактирования
void MainWindow::ReportMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    std::wstring msg;
    // Найти сообщений в карте сообщений
    if (mainWindow->observedMessageMap.count(message) > 0)
    {
        msg = mainWindow->observedMessageMap[message];
    }    
    else
    {
        msg = std::to_wstring(message);
    }

    // Построить сообщение
    std::wostringstream oss;
    oss << msg << ": wparam = 0x" << std::hex << wParam << ", lparam = 0x" << std::hex << lParam << L"\r\n";
    std::wstring line = oss.str();

    
    // Очисить EDIT если размер текста превышает лимит
    int currLen = GetWindowTextLength(hInfoEdit);
    UINT maxLen = SendMessage(hInfoEdit, EM_GETLIMITTEXT, 0, 0);
    if (currLen + line.length() > maxLen)
    {
        SetWindowText(hInfoEdit, L"");
    }

    // Добавить сообщение в конец ЭУ
    SendMessage(hInfoEdit, EM_REPLACESEL, FALSE, (LPARAM)line.c_str());
    SendMessage(hInfoEdit, EM_LINESCROLL, 0, 1);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}