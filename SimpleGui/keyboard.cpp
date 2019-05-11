#include "keyboard.h"

#include <functions.h>

bool* Keyboard::keys_ = nullptr;

Keyboard Keyboard::keyboardInitializer_;

bool Keyboard::isKeyPressed(Key key)
{
    if (key >= Key::Backspace && key <= Key::OemClear) {
        return keys_[static_cast<short>(key)];
    }
    return false;
}

const bool* Keyboard::getKeyArray()
{
    return keys_;
}

Keyboard::Keyboard()
{
    keys_ = new bool[200'000];
    memset(keys_, 0, 200'000);
}

Keyboard::~Keyboard()
{
    delete[] keys_;
}
