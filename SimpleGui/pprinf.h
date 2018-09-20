#ifndef PPRINF_H
#define PPRINF_H

#include <Windows.h>

class PrivateProcessInformation {
public:
    static HINSTANCE getHInstance();

    static void setHInstance(HINSTANCE value);

private:
    static HINSTANCE hInstance_;

};

#endif // PPRINF_H