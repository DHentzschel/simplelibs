#include "ikeycallback.h"

#include <functions.h>
#include "keyboard.h"

void IKeyCallback::invokeCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    if (key > -1) {
        Keyboard::keys_[key] = STATIC_CAST(InputAction, action) == InputAction::Press;
    }
    invoke(window, STATIC_CAST(Key, key), scancode, STATIC_CAST(InputAction, action), STATIC_CAST(byte, mods));
}
