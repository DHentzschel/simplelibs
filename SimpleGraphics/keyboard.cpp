#include "keyboard.h"

#include <functions.h>
#include <memory>

bool* Keyboard::keys_ = nullptr;

Keyboard Keyboard::keyboardInitializer;

Keyboard::Keyboard()
{
    if (keys_ == nullptr) {
        keys_ = new bool[arraySize_];
        memset(keys_, false, arraySize_ * sizeof(bool));
    }
}

Keyboard::~Keyboard()
{
    delete[] keys_;
}

bool Keyboard::isKeyPressed(Key key) const
{
    return keys_[static_cast<int>(key)];
}
