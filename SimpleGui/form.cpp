#include "form.h"

#include <Windows.h>

#include <functions.h>
#include <vector2.h>

#include "pprinf.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class FormPrivate {
public:
    FormPrivate();

    void initialize();

    void setPosition(int x, int y);

    void setSize(int x, int y);

    void show();

    MSG msg;

    HWND hwnd;

    WNDCLASSW wc;

    Vector2 position;

    Vector2 size;
};

Form::Form() :
    private_(new FormPrivate())
{
}

Form::~Form()
{
    delete private_;
}

void Form::setPosition(int x, int y)
{
    private_->setPosition(x, y);
}

void Form::setSize(int x, int y)
{
    private_->setSize(x, y);
}

void Form::show() {
    private_->show();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

FormPrivate::FormPrivate() :
    position(Vector2(0, 0)),
    size(Vector2(100, 100))
{
    initialize();
}

void FormPrivate::initialize()
{
    HINSTANCE hinstance = PrivateProcessInformation::getHInstance();
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszClassName = L"className";
    wc.hInstance = STATIC_CAST(HINSTANCE, hinstance);
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassW(&wc);
    hwnd = CreateWindowW(wc.lpszClassName, L"Window title",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, position.x, position.y, size.x, size.y, NULL, NULL, hinstance, NULL);
}

void FormPrivate::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    MoveWindow(hwnd, position.x, position.y, size.x, size.y, true);
}

void FormPrivate::setSize(int x, int y)
{
    size.x = x;
    size.y = y;
    MoveWindow(hwnd, position.x, position.y, size.x, size.y, true);
}

void FormPrivate::show()
{
    ShowWindow(hwnd, 10);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
}
