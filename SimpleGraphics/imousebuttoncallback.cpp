#include "imousebuttoncallback.h"

#include <functions.h>

#include "mouse.h"

void IMouseButtonCallback::invokeCallback(GLFWwindow* window, int button, int action, int mods)
{
    Mouse::buttons_[button] = static_cast<InputAction>(action) == InputAction::Press;
    invoke(window, static_cast<Key>(button), static_cast<InputAction>(action), static_cast<byte>(mods));
}
