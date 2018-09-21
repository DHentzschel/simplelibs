#include "msgbox.h"

#include <Windows.h>

#include "mbbuttons.h"
#include "mbicons.h"

MsgBox::MsgBox()
{
}

MsgBox::~MsgBox()
{
}

MbResult MsgBox::error(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcons::Error)));
}

MbResult MsgBox::information(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcons::Information)));
}

MbResult MsgBox::question(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcons::Question)));
}

MbResult MsgBox::warning(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcons::Warning)));
}
