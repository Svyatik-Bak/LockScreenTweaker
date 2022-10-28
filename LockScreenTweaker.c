#include <windows.h>
#include <stdbool.h>
#include <SB_registry.h>
#include "resource.h"
#define BUT1_ID 100
#define BUT2_ID 200
#define BUT3_ID 300
#define BUT4_ID 400

LRESULT CALLBACK WindowFunc(HWND hWnd, UINT Message,WPARAM wParam,LPARAM lParam){
    HWND CLogo;
    HBITMAP Picture;
    char copyright[100];
    HMENU hMenu, hSubMenu;
    HICON hIcon, hIconSm;
    LPCREATESTRUCT pCreat = (LPCREATESTRUCT) lParam;
    switch(Message) 
    {
        case WM_CREATE:
        HWND hiding = GetConsoleWindow();
        ShowWindow(hiding, SW_HIDE);
        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_STUFF_ABOUT, "About");
        AppendMenu(hSubMenu, MF_STRING, ID_STUFF_EXIT, "Exit");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, "Stuff");
        SetMenu(hWnd, hMenu);
        HWND butt1 = CreateWindow("button", "Disable Lock Screen", WS_VISIBLE | WS_CHILD, 170, 440, 150, 35, hWnd, (HMENU) BUT1_ID, NULL, NULL); 
        HWND butt2 = CreateWindow("button", "Enable Lock Screen", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 170, 490, 150, 35, hWnd, (HMENU) BUT2_ID, NULL, NULL);
        HWND butt3 = CreateWindow("button", "Disable Blur", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 400, 440, 150, 35, hWnd, (HMENU) BUT3_ID, NULL, NULL); 
        HWND butt4 = CreateWindow("button", "Enable Blur", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 400, 490, 150, 35, hWnd, (HMENU) BUT4_ID, NULL, NULL);
        Picture = (HBITMAP)LoadImage(pCreat->hInstance, MAKEINTRESOURCE(IDB_PICTURE), IMAGE_BITMAP, 700, 400, 0);
        CLogo = CreateWindow("Static", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 35, 20, 150, 30, hWnd, NULL, NULL, NULL);
        SendMessage(CLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Picture);
        case WM_SETFONT:
        NONCLIENTMETRICS metrics = {};
        metrics.cbSize = sizeof(metrics);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);
        HFONT guiFont = CreateFontIndirect(&metrics.lfCaptionFont);
        SendMessage(butt1, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(butt2, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(butt3, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        SendMessage(butt4, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        DeleteObject(guiFont);
        case WM_COMMAND:
      if (LOWORD(wParam) == 100)
      {
         SRCreateKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization");
         SRCreateValue_DWORD(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization", L"NoLockScreen", 0x000001);
      }

      if (LOWORD(wParam) == 200)
      {
         SRCreateValue_DWORD(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Personalization", L"NoLockScreen", 0x000000);
      }

      if (LOWORD(wParam) == 300)
      {
         SRCreateKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System");
         SRCreateValue_DWORD(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableAcrylicBackgroundOnLogon", 0x000001);
      }

      if (LOWORD(wParam) == 400)
      {
         SRCreateValue_DWORD(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableAcrylicBackgroundOnLogon", 0x000000);
      }

      if (LOWORD(wParam) == 106)
      {
         exit(0);
      }
      if (LOWORD(wParam) == 105)
      {
         MessageBox(NULL, "(C) Svyatik Bak \nGUI: WindowsAPI\nhttps://svyatik-bak.github.io/index.en-us.html", "About", MB_ICONINFORMATION | MB_OK);
      } break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(hWnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode)
{
 WNDCLASSEX WinClass = { 0 };
 WinClass.cbSize        = sizeof(WNDCLASSEX);
 WinClass.hInstance     = hThisInst;
 WinClass.lpszClassName = "something";
 WinClass.lpfnWndProc   = WindowFunc;
 WinClass.style         = 0;
 WinClass.lpszMenuName  = MAKEINTRESOURCE(IDR_MYSTUPIDMENU);
 WinClass.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYAPP_ICON));
 WinClass.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYAPP_ICON), IMAGE_ICON, 16, 16, 0);
 WinClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
 WinClass.lpszMenuName  = NULL;
 WinClass.cbClsExtra    = 0;
 WinClass.cbWndExtra    = 0;

 if (!RegisterClassEx(&WinClass)) 
 {
    MessageBox(NULL, "Something ununexpected happened", "Oops", MB_ICONERROR | MB_OK);
    return 1;
 }

 HWND hWnd = CreateWindow("something", "Lock Screen Tweaker", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hThisInst, NULL);

 ShowWindow(hWnd, WinMode);
 UpdateWindow(hWnd);
 MSG Message;

 while (GetMessage(&Message, NULL, 0, 0) > 0)
 {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
 }
 return Message.wParam;
}