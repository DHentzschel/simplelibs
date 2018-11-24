#include "imousebuttoncallback.h"

#include <functions.h>

#include "mouse.h"

void IMouseButtonCallback::invokeCallback(GLFWwindow* window, int button, int action, int mods)
{
    Mouse::buttons_[button] = STATIC_CAST(InputAction, action) == InputAction::Press;
    invoke(window, STATIC_CAST(Key, button), STATIC_CAST(InputAction, action), STATIC_CAST(byte, mods));
}
