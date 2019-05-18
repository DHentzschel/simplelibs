#include "outputbox.h"

#include <Windows.h>

OutputBox::OutputBox() :
    OutputBox("empty", "empty")
{}

OutputBox::OutputBox(const AString& text, const AString& title, ObIcon icon,
    ObButtons buttons, ObDefaultButton defaultButton) :
    text_(text),
    title_(title),
    icon_(icon),
    buttons_(buttons),
    defaultButton_(defaultButton)
{}

void OutputBox::setText(const AString& value)
{
    text_ = value;
}

void OutputBox::setTitle(const AString& value)
{
    title_ = value;
}

void OutputBox::setIcon(ObIcon value)
{
    icon_ = value;
}

void OutputBox::setButtons(ObButtons value)
{
    buttons_ = value;
}

void OutputBox::setDefaultButton(ObDefaultButton value)
{
    defaultButton_ = value;
}

ObResult OutputBox::show()
{
    // TODO: Implement parent ptr
    return ObResultUtils::get(MessageBoxA(/*parent*/ 0, text_.toCString(), title_.toCString(),
        static_cast<int>(buttons_) | static_cast<int>(defaultButton_) | static_cast<int>(icon_)));
}

ObResult OutputBox::error(const AString & text, const AString & title, ObButtons buttons, ObDefaultButton defaultButton)
{
    return OutputBox(text, title, ObIcon::Error, buttons, defaultButton).show();
}

ObResult OutputBox::information(const AString & text, const AString & title, ObButtons buttons, ObDefaultButton defaultButton)
{
    return OutputBox(text, title, ObIcon::Information, buttons, defaultButton).show();
}

ObResult OutputBox::question(const AString & text, const AString & title, ObButtons buttons, ObDefaultButton defaultButton)
{
    return OutputBox(text, title, ObIcon::Question, buttons, defaultButton).show();
}

ObResult OutputBox::warning(const AString & text, const AString & title, ObButtons buttons, ObDefaultButton defaultButton)
{
    return OutputBox(text, title, ObIcon::Warning, buttons, defaultButton).show();
}
