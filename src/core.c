#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Advapi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst = NULL;

int mousedown = 0;
POINT lastLocation;
HCURSOR hCursor;    ///sasasa

/// @brief entry point to code
/*!
 * @return int error code
 */
int main()
{
    char Buf[1024];
    INT32 len = 1024;
    RegGetValueW(HKEY_LOCAL_MACHINE,
                 L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\RAGE Multiplayer", L"DisplayIcon", RRF_RT_DWORD, NULL, &Buf, &len);
    for (int i = 0; i < len; i++)
    {
        printf("%c", Buf[i]);
    }

    hInst = GetModuleHandle(0);
    MSG msg;
    WNDCLASSW wc = {0};

    hCursor = LoadCursorW(hInst, L"A_CURSOR");

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"A_LAUNCHER";
    wc.hInstance = hInst;
    wc.hIcon = LoadIconW(hInst, L"A_ICON");
    // wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = hCursor;

    RegisterClassW(&wc);
    HWND hWnd = CreateWindowW(wc.lpszClassName, L"AbsoluteDM Launcher",
                              WS_BORDER,
                              300, 200, 1000, 650, NULL, NULL, hInst, NULL);
    SetWindowLong(hWnd, GWL_STYLE, 0);
    ShowWindow(hWnd, SW_SHOW);

    while (GetMessage(&msg, NULL, 0, 0))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                         WPARAM wParam, LPARAM lParam)
{

    static HBITMAP hBitmapBackground;
    static HBITMAP hBitmapExit;
    static HBITMAP hBitmapMin;
    static HBITMAP hBitmapSet;
    HDC hdc;
    PAINTSTRUCT ps;
    BITMAP bitmapBackground;
    BITMAP bitmapExit;
    HDC hdcMem;
    HGDIOBJ oldBitmap;

    // printf("%x\n",msg);
    switch (msg)
    {

    case WM_CREATE:

        hBitmapBackground = (HBITMAP)LoadImageW(hInst, L"A_BCKGRND",
                                                IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

        if (hBitmapBackground == NULL)
        {
            MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK);
        }

        hBitmapExit = (HBITMAP)LoadImageW(hInst, L"A_EXIT",
                                          IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

        if (hBitmapExit == NULL)
        {
            MessageBoxW(hwnd, L"Failed to load image exit", L"Error", MB_OK);
        }
        hBitmapMin = (HBITMAP)LoadImageW(hInst, L"A_MIN",
                                         IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

        if (hBitmapMin == NULL)
        {
            MessageBoxW(hwnd, L"Failed to load image min", L"Error", MB_OK);
        }
        hBitmapSet = (HBITMAP)LoadImageW(hInst, L"A_SET",
                                         IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

        if (hBitmapSet == NULL)
        {
            MessageBoxW(hwnd, L"Failed to load image set", L"Error", MB_OK);
        }

        HWND hwndSetSC = CreateWindowW(
            L"STATIC",                                     // Predefined class; Unicode assumed
            L"",                                           // Button text
            SS_NOTIFY | SS_BITMAP | WS_CHILD | WS_VISIBLE, // Styles
            860,                                           // x position
            12,                                            // y position
            35,                                            // Button width
            35,                                            // Button height
            hwnd,                                          // Parent window
            (HMENU)1002,                                   // No menu.
            NULL,
            NULL); // Pointer not needed.

        HWND hwndMinSC = CreateWindowW(
            L"STATIC",                                     // Predefined class; Unicode assumed
            L"",                                           // Button text
            SS_NOTIFY | SS_BITMAP | WS_CHILD | WS_VISIBLE, // Styles
            905,                                           // x position
            12,                                            // y position
            35,                                            // Button width
            35,                                            // Button height
            hwnd,                                          // Parent window
            (HMENU)1001,                                   // No menu.
            NULL,
            NULL); // Pointer not needed.

        HWND hwndExitSC = CreateWindowW(
            L"STATIC",                                     // Predefined class; Unicode assumed
            L"",                                           // Button text
            SS_NOTIFY | SS_BITMAP | WS_CHILD | WS_VISIBLE, // Styles
            950,                                           // x position
            12,                                            // y position
            35,                                            // Button width
            35,                                            // Button height
            hwnd,                                          // Parent window
            (HMENU)1000,                                   // No menu.
            NULL,
            NULL);

        SendMessage(hwnd, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);
        SendMessageW(hwndExitSC, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmapExit);
        SendMessageW(hwndMinSC, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmapMin);
        SendMessageW(hwndSetSC, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmapSet);
        break;

        //         case WM_LBUTTONDOWN: {
        //             mousedown = 1;
        //             GetCursorPos(&lastLocation);
        //             RECT rect;
        //             GetWindowRect(hwnd, &rect);
        //             lastLocation.x = lastLocation.x - rect.left;
        //             lastLocation.y = lastLocation.y - rect.top;
        //             break;
        // }

    case WM_MOUSEMOVE:
        printf("sasasas");

        POINT currentpos;
        GetCursorPos(&currentpos);
        printf("%d", WindowFromPoint(currentpos));
        // if(WindowFromPoint(currentpos)==hwndSetSC){
        // printf("sasasas");
        //}
        break;

    case WM_NCHITTEST:
        // LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
        // if (hit == HTCLIENT) hit = HTCAPTION;
        SetCursor(hCursor);
        return HTCAPTION;
        break;

    case WM_COMMAND:
        if (HIWORD(wParam) == STN_CLICKED)
        {
            if (LOWORD(wParam) == 1000)
            {
                DeleteObject(hBitmapBackground);
                PostQuitMessage(0);

                return 0;
            }
            else if (LOWORD(wParam) == 1001)
            {
                ShowWindow(hwnd, SW_MINIMIZE);
            }
        }
        break;

        break;

    case WM_SETCURSOR:

        SetCursor(hCursor);

        return;

    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);

        hdcMem = CreateCompatibleDC(hdc);
        oldBitmap = SelectObject(hdcMem, hBitmapBackground);

        GetObject(hBitmapBackground, sizeof(bitmapBackground), &bitmapBackground);
        BitBlt(hdc, 0, 0, bitmapBackground.bmWidth, bitmapBackground.bmHeight,
               hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);

        EndPaint(hwnd, &ps);

        break;

    case WM_DESTROY:

        DeleteObject(hBitmapBackground);
        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}