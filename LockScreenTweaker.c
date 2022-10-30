#include <windows.h>
#include <stdbool.h>
#include <SB_registry.h> // My library https://github.com/Svyatik-Bak/SB_registry.h
#include "resource.h"
#define BUT1_ID 100 
#define BUT2_ID 200
#define BUT3_ID 300
#define BUT4_ID 400

LRESULT CALLBACK WindowFunc(HWND window, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HWND CPicture; HBITMAP Picture;
    HMENU hMenu, hSubMenu; HICON hIcon, hIconSm;
    LPCREATESTRUCT pCreat = (LPCREATESTRUCT) lParam;
    switch(Message) 
    {
        case WM_CREATE:
        //Hiding command prompt
        HWND hiding = GetConsoleWindow();
        ShowWindow(hiding, SW_HIDE);
        // Creating menus
        hMenu = CreateMenu(); hSubMenu = CreatePopupMenu();
        AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"Stuff");
        AppendMenuW(hSubMenu, MF_STRING, ID_STUFF_GITHUB, L"My Github"); AppendMenuW(hSubMenu, MF_STRING, ID_STUFF_UTUB, L"My YouTube");
        AppendMenuW(hSubMenu, MF_STRING, ID_STUFF_SITE, L"My Site"); AppendMenuW(hSubMenu, MF_STRING, ID_STUFF_ABOUT, L"About");
        AppendMenuW(hSubMenu, MF_STRING, ID_STUFF_EXIT, L"Exit");
        SetMenu(window, hMenu);
        // Creating buttons
        HWND butt1 = CreateWindowW(L"button", L"Disable Lock Screen", WS_VISIBLE | WS_CHILD, 170, 440, 150, 35, window, (HMENU) BUT1_ID, NULL, NULL); 
        HWND butt2 = CreateWindowW(L"button", L"Enable Lock Screen", WS_VISIBLE | WS_CHILD, 170, 490, 150, 35, window, (HMENU) BUT2_ID, NULL, NULL);
        HWND butt3 = CreateWindowW(L"button", L"Disable Blur", WS_VISIBLE | WS_CHILD, 400, 440, 150, 35, window, (HMENU) BUT3_ID, NULL, NULL); 
        HWND butt4 = CreateWindowW(L"button", L"Enable Blur", WS_VISIBLE | WS_CHILD, 400, 490, 150, 35, window, (HMENU) BUT4_ID, NULL, NULL);
        // Loading a picture
        Picture = (HBITMAP)LoadImageW(pCreat->hInstance, MAKEINTRESOURCEW(IDB_PICTURE), IMAGE_BITMAP, 700, 400, 0);
        CPicture = CreateWindowW(L"Static", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 35, 20, 150, 30, window, NULL, NULL, NULL);
        SendMessageW(CPicture, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Picture);
        // Changing font on the buttons
        case WM_SETFONT:
        NONCLIENTMETRICS metrics = {}; metrics.cbSize = sizeof(metrics);
        SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0); HFONT guiFont = CreateFontIndirect(&metrics.lfCaptionFont);
        SendMessageW(butt1, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true); SendMessageW(butt3, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true); 
        SendMessageW(butt2, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true); SendMessageW(butt4, WM_SETFONT, (LPARAM)GetStockObject(DEFAULT_GUI_FONT), true);
        DeleteObject(guiFont);
        //Events for buttons and menu
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
         MessageBoxW(NULL, L"(C) Svyatik Bak \nGUI: Windows API\nhttps://svyatik-bak.github.io/index.en-us.html", L"About", MB_ICONINFORMATION | MB_OK);
      } 
      
      if (LOWORD(wParam) == 107)
      {
         ShellExecuteW(NULL, L"open", L"https://github.com/Svyatik-Bak", NULL, NULL, SW_SHOW);
      }
      
      if (LOWORD(wParam) == 108)
      {
         ShellExecuteW(NULL, L"open", L"https://www.youtube.com/SvyatikBak", NULL, NULL, SW_SHOW);
      }
      
      if (LOWORD(wParam) == 109)
      {
         ShellExecuteW(NULL, L"open", L"https://svyatik-bak.github.io/index.en-us", NULL, NULL, SW_SHOW);
      } break;
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(window, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode)
{
// Some classes
 WNDCLASSEX wc = { 0 }; wc.cbSize = sizeof(WNDCLASSEX);
 wc.hInstance = hThisInst; wc.lpszClassName = "something";
 wc.lpfnWndProc = WindowFunc; wc.style = 0;
 wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYSTUPIDMENU); wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYAPP_ICON));
 wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYAPP_ICON), IMAGE_ICON, 16, 16, 0); wc.hCursor = LoadCursor(NULL, IDC_ARROW);
 wc.lpszMenuName = NULL; wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
 wc.cbClsExtra = 0; wc.cbWndExtra = 0;

// Classes registration error
 if (!RegisterClassEx(&wc)) 
 {
    MessageBoxW(NULL, L"Something ununexpected happened", L"Oops", MB_ICONERROR | MB_OK);
    return 1;
 }

 // Main window
 HWND window = CreateWindowW(L"something", L"Lock Screen Tweaker", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 540, 200, 800, 600, NULL, NULL, hThisInst, NULL);

 ShowWindow(window, WinMode);
 UpdateWindow(window);
 MSG Message;

 while (GetMessage(&Message, NULL, 0, 0) > 0)
 {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
 }
 return Message.wParam;
}