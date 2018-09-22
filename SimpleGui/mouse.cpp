#include "mouse.h"

#include "keyboard.h"

bool* Mouse::keys_ = nullptr;

Vector2 Mouse::position_;

Mouse Mouse::mouseInitializer_;

Mouse::Mouse()
{
    keys_ = CONST_CAST(bool*, Keyboard::getKeyArray());
}

bool Mouse::isButtonPressed(Key key)
{
    if (key >= Key::MouseLeft && key <= Key::MouseX2) {
        return keys_[STATIC_CAST(short, key)];
    }
    return false;
}

Vector2& Mouse::getPosition()
{
    return position_;
}
