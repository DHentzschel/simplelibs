#include "ikeycallback.h"

#include <functions.h>
#include "keyboard.h"

void IKeyCallback::invokeCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key > -1) {
        Keyboard::keys_[key] = static_cast<InputAction>(action) == InputAction::Press;
    }
    invoke(window, static_cast<Key>(key), scancode, static_cast<InputAction>(action), static_cast<byte>(mods));
}
