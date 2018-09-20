#include "pprinf.h"

HINSTANCE PrivateProcessInformation::hInstance_;

HINSTANCE PrivateProcessInformation::getHInstance()
{
    return hInstance_;
}

void PrivateProcessInformation::setHInstance(HINSTANCE value)
{
    hInstance_ = value;
}
