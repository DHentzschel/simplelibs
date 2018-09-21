#include "msgbox.h"

#include <Windows.h>

#include "mbbuttons.h"

MsgBox::MsgBox() :
    MsgBox("empty", "empty")
{
}

MsgBox::MsgBox(const AString& text, const AString& title, MbIcon icon,
    MbButtons buttons, MbDefaultButton defaultButton) :
    text_(text),
    title_(title),
    icon_(icon),
    buttons_(buttons),
    defaultButton_(defaultButton)
{
}

void MsgBox::setText(const AString& value)
{
    text_ = value;
}

void MsgBox::setTitle(const AString& value)
{
    title_ = value;
}

void MsgBox::setIcon(MbIcon value)
{
    icon_ = value;
}

void MsgBox::setButtons(MbButtons value)
{
    buttons_ = value;
}

void MsgBox::setDefaultButton(MbDefaultButton value)
{
    defaultButton_ = value;
}

MbResult MsgBox::show()
{
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text_.toCString(), title_.toCString(),
        STATIC_CAST(int, buttons_) | STATIC_CAST(int, defaultButton_) | STATIC_CAST(int, icon_)));
}

MbResult MsgBox::error(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    return MsgBox(text, title, MbIcon::Error, buttons, defaultButton).show();
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcon::Error)));
}

MbResult MsgBox::information(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    return MsgBox(text, title, MbIcon::Information, buttons, defaultButton).show();
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcon::Information)));
}

MbResult MsgBox::question(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    return MsgBox(text, title, MbIcon::Question, buttons, defaultButton).show();
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcon::Question)));
}

MbResult MsgBox::warning(const AString& text, const AString& title, MbButtons buttons, MbDefaultButton defaultButton)
{
    return MsgBox(text, title, MbIcon::Warning, buttons, defaultButton).show();
    // TODO: Implement parent ptr
    return MbResultUtils::get(MessageBoxA(/*parent*/ 0, text.toCString(), title.toCString(),
        STATIC_CAST(int, buttons) | STATIC_CAST(int, defaultButton) | STATIC_CAST(int, MbIcon::Warning)));
}
