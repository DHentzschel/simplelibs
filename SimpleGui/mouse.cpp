#include "mouse.h"

#include "keyboard.h"

bool* Mouse::keys_ = nullptr;

Vector2i Mouse::position_;

Mouse Mouse::mouseInitializer_;

Mouse::Mouse()
{
    keys_ = const_cast<bool*>(Keyboard::getKeyArray());
}

bool Mouse::isButtonPressed(Key key)
{
    if (key >= Key::MouseLeft && key <= Key::MouseX2) {
        return keys_[static_cast<short>(key)];
    }
    return false;
}

Vector2i& Mouse::getPosition()
{
    return position_;
}
