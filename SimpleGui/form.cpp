#include "form.h"

#include <Windows.h>

#include <alist.h>
#include <functions.h>
#include <vector2.h>

#include "pprinf.h"
#include "screen.h"

#include "outputbox.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class FormPrivate {
public:
    FormPrivate(Form* form);

    void initialize();

    void setPosition(int x, int y);

    void centerToScreen();

    void setSize(int x, int y);

    void setIsMaximized(bool value);

    void setIsMinimized(bool value);

    void setWindowTitle(const AString& title);

    void hide();

    void show();

    /* Events */
    void processEvents();

    void invokeFormMovedEvent();

    void invokeFormResizedEvent();

    void invokeFormSizeEvent(WPARAM wParam, LPARAM lParam);

    void invokeFormGainedFocusEvent();

    void invokeFormLostFocusEvent();

    void invokeFormClosedEvent();

    void invokeFormShownEvent(WPARAM wParam);

    void invokeFormPositionChangedEvent(LPARAM lParam);

    void invokeFormPositionChangingEvent(LPARAM lParam);

    /* WINAPI attributes */
    MSG msg;

    HWND hwnd;

    WNDCLASSW wc;

    /* Attributes */
    Vector2 previousPosition;

    Vector2 position;

    Vector2 previousSize;

    Vector2 size;

    bool isShown;

    bool isMaximized;

    bool isMinimized;

    Form* form;

    static FormPrivate* get(HWND hwnd);

    static AList<Form*> formList_;
};

AList<Form*> FormPrivate::formList_;

Form::Form() :
    private_(new FormPrivate(this))
{
    private_->formList_.append(this);
}

Form::~Form()
{
    private_->formList_.removeFirst(this);
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

void Form::setIsMaximized(bool value)
{
    private_->setIsMaximized(value);
}

void Form::setIsMinimized(bool value)
{
    private_->setIsMinimized(value);
}

void Form::setWindowTitle(const AString& title)
{
    private_->setWindowTitle(title);
}

void Form::hide()
{
    private_->hide();
}

void Form::show() {
    private_->show();
}

FormPrivate::FormPrivate(Form* form) :
    position(Vector2(100, 100)),
    size(Vector2(100, 100)),
    form(form)
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
    hwnd = CreateWindowW(wc.lpszClassName, L"Form",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, position.x, position.y, size.x, size.y, NULL, NULL, hinstance, NULL);
}

void FormPrivate::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
    MoveWindow(hwnd, position.x, position.y, size.x, size.y, true);
}

void FormPrivate::centerToScreen()
{
    const auto screenSize = Screen::getSize();
    setPosition(STATIC_CAST(int, (screenSize.x - size.x) * 0.5F), STATIC_CAST(int, (screenSize.y - size.y) * 0.5F));
}

void Form::centerToScreen()
{
    private_->centerToScreen();
}

void FormPrivate::setSize(int x, int y)
{
    size.x = x;
    size.y = y;
    MoveWindow(hwnd, position.x, position.y, size.x, size.y, true);
}

void FormPrivate::setIsMaximized(bool value)
{
    isMaximized = value;

    if (isShown) {
        ShowWindow(hwnd, (isMaximized ? SW_SHOWMAXIMIZED : SW_SHOWDEFAULT));
    }
}

void FormPrivate::setIsMinimized(bool value)
{
    isMinimized = value;

    if (isShown) {
        ShowWindow(hwnd, (isMinimized ? SW_SHOWMAXIMIZED : SW_SHOWDEFAULT));
    }
}

void FormPrivate::setWindowTitle(const AString& title)
{
    SetWindowTextA(hwnd, title.toCString());
}

void FormPrivate::hide()
{
    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);
    isShown = false;
}

void FormPrivate::show()
{
    ShowWindow(hwnd, (isMaximized ? SW_SHOWMAXIMIZED : (isMinimized ? SW_SHOWMINIMIZED : SW_SHOWDEFAULT)));
    UpdateWindow(hwnd);
    isShown = true;
    processEvents();
}

void FormPrivate::processEvents()
{
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }
}

void FormPrivate::invokeFormMovedEvent()
{
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);

    Vector2 newPosition(windowRect.left, windowRect.top);
    previousPosition = position;
    position = newPosition;

    form->formMovedEvent(previousPosition, newPosition);
}

void FormPrivate::invokeFormResizedEvent()
{
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);

    Vector2 newSize(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    previousSize = size;
    size = newSize;

    form->formResizedEvent(previousSize, size);
}

void FormPrivate::invokeFormSizeEvent(WPARAM wParam, LPARAM lParam)
{
    auto size = Vector2(STATIC_CAST(int, lParam) & 0xFFFF, STATIC_CAST(int, lParam) >> 16);

    switch (wParam) {
    case SIZE_MAXIMIZED:
        form->formMaximizedEvent(size);
        break;
    case SIZE_MINIMIZED:
        form->formMinimizedEvent(size);
        break;
    case SIZE_RESTORED:
        form->formRestoredEvent(size);
        break;
    }
}

void FormPrivate::invokeFormGainedFocusEvent()
{
    form->formGainedFocusEvent();
}

void FormPrivate::invokeFormLostFocusEvent()
{
    form->formLostFocusEvent();
}

void FormPrivate::invokeFormClosedEvent()
{
    form->formClosedEvent();
}

void FormPrivate::invokeFormShownEvent(WPARAM wParam)
{
    form->formShownEvent(STATIC_CAST(bool, wParam));
}

void FormPrivate::invokeFormPositionChangedEvent(LPARAM lParam)
{
    WINDOWPOS& windowPos = *(WINDOWPOS*)lParam;
    form->formPositionChangedEvent(Vector2(windowPos.x, windowPos.y));
}

void FormPrivate::invokeFormPositionChangingEvent(LPARAM lParam)
{
    WINDOWPOS& windowPos = *(WINDOWPOS*)lParam;
    form->formPositionChangingEvent(Vector2(windowPos.x, windowPos.y));
}

FormPrivate* FormPrivate::get(HWND hwnd)
{
    for (auto* form : formList_) {
        if (form->private_->hwnd == hwnd) {
            return form->private_;
        }
    }
    return nullptr;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    auto* formPrivate = FormPrivate::get(hwnd);
    if (formPrivate != nullptr) {
        switch (msg) {
        case WM_CREATE:
            OutputBox::information("", "");
            // form create event ?
            break;
        case WM_DESTROY:
            // dtor
            PostQuitMessage(0);
            break;
        case WM_MOVE:
            formPrivate->invokeFormMovedEvent();
            break;
        case WM_SIZING:
            formPrivate->invokeFormResizedEvent();
            break;
        case WM_SIZE:
            formPrivate->invokeFormSizeEvent(wParam, lParam);
            break;
        case WM_SETFOCUS:
            formPrivate->invokeFormGainedFocusEvent();
            break;
        case WM_KILLFOCUS:
            formPrivate->invokeFormLostFocusEvent();
            break;
        case WM_CLOSE:
            formPrivate->invokeFormClosedEvent();
            break;
        case WM_SHOWWINDOW:
            formPrivate->invokeFormShownEvent(wParam);
            break;
        case WM_WINDOWPOSCHANGED:
            formPrivate->invokeFormPositionChangedEvent(lParam);
            break;
        case WM_WINDOWPOSCHANGING:
            formPrivate->invokeFormPositionChangingEvent(lParam);
            break;
        }
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}
