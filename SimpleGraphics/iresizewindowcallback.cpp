#include "iresizewindowcallback.h"

#include "imaximizewindowcallback.h"
#include "iminimizewindowcallback.h"
#include "monitor.h"
#include "window.h"

void IResizeWindowCallback::invokeCallback(GLFWwindow* window, int width, int height)
{
    Vector2 size(width, height);
    Vector2 monitorSize(Monitor::getSize());

    if (minimizeWindowCallback_ != nullptr && size.x == 0 && size.y == 0) {
        minimizeWindowCallback_->invokeCallback(window);
    }
    else if (maximizeWindowCallback_ != nullptr && size.x == monitorSize.x && size.y >= monitorSize.y - 53) {
        maximizeWindowCallback_->invokeCallback(window, size);
    }
    else {
        invoke(window, size);
    }

    Window::size_ = size;
}
