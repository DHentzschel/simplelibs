#include "control.h"

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*'\
publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "msimg32.lib")

#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>

#include "outputbox.h"
#include "pprinf.h"

#define IDC_BTNADDENTRY 100

Control::Control()
{
}

LRESULT CALLBACK SubclassEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WNDPROC wpOld = (WNDPROC)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    LRESULT lrResult = 0;

    if (wpOld) {
        switch (uMsg)
        {
            // Draw fancy gradient background in log edit control
        case WM_ERASEBKGND:
        {
            RECT rc;
            if (GetClientRect(hWnd, &rc)) {
                INT nW = (rc.right - rc.left);
                INT nH = (rc.bottom - rc.top);
                TRIVERTEX triVertex[5] = {
                    {  0, nH,	 0xFF00, 0xFF00, 0xFF00, 0x0000 },
                    { nW, nH / 2, 0xFF00, 0xFF00, 0xFF00, 0x0000 },
                    { nW, nH,	 0xBB00, 0xDD00, 0xF700, 0x0000 },
                };
                GRADIENT_TRIANGLE triMesh = { 0, 1, 2 };
                HDC hdc = (HDC)wParam;
                INT ndc = SaveDC(hdc);
                SetBkColor(hdc, RGB(255, 255, 255));
                ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
                GradientFill(hdc, triVertex, 3, &triMesh, 1, GRADIENT_FILL_TRIANGLE);
                RestoreDC(hdc, ndc);
                return 0;
            }
        }
        break;

        // Last message to a window so we de-subclass ourselves.
        case WM_NCDESTROY:
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)wpOld);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
            break;

            // Sent by IsDialogMessage() API to determine what keys the control wants.
            // We use this to forward the tab key so it selects the next control.
        case WM_GETDLGCODE:
            lrResult = CallWindowProc(wpOld, hWnd, uMsg, wParam, lParam);
            lrResult &= ~(DLGC_HASSETSEL | DLGC_WANTTAB);
            if (lParam && ((LPMSG)lParam)->message == WM_KEYDOWN &&
                ((LPMSG)lParam)->wParam == VK_TAB)
                lrResult &= ~DLGC_WANTMESSAGE;
            return lrResult;
        }

        // Call the original window procedure.
        return CallWindowProc(wpOld, hWnd, uMsg, wParam, lParam);
    }

    // Crap couldn't find the original window procedure... use default.
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HFONT g_hfText;
void Control::create()
{
    if (hwndWindow_ == nullptr) {
        OutputBox::error("Ptr hwndWindow_ is nullptr.", "Error");
    }

    hwnd_ = CreateWindowEx(0, WC_BUTTON, TEXT("&Test"),
        BS_PUSHBUTTON | BS_TEXT |
        WS_CHILD | WS_TABSTOP | WS_VISIBLE,
        0, 0, 0, 0, hwndWindow_, (HMENU)IDC_BTNADDENTRY, PrivateProcessInformation::getHInstance(), NULL);
    if (!hwnd_)
        return;
    // Set the button controls properties.
    SendMessage(hwnd_, WM_SETFONT, (WPARAM)g_hfText, FALSE);
}

void Control::show()
{
    ShowWindow(hwnd_, SW_SHOW);
    UpdateWindow(hwnd_);
}

void Control::setHwnd(HWND hwnd)
{
    hwndWindow_ = hwnd;
}
