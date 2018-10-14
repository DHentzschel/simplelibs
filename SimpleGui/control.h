#ifndef CONTROL_H
#define CONTROL_H

#include <Windows.h>

class Control {
    friend class Form;

    friend class FormPrivate;

public:
    Control();

private:
    HWND hwnd_;

    HWND hwndWindow_;

    void create();

    void show();

    void setHwnd(HWND hwnd);
};

#endif // CONTROL_H
