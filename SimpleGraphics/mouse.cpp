#include "mouse.h"

#include <GLFW/glfw3.h>

#include <memory>
#include <functions.h>
#include <types.h>

#include "window.h"

bool* Mouse::buttons_ = nullptr;

Mouse Mouse::mouseInitializer_;

Window* Mouse::window_ = nullptr;

Mouse::Mouse()
{
    if (buttons_ == nullptr) {
        buttons_ = new bool[8];
        memset(buttons_, false, 8 * sizeof(bool));
    }
}

Mouse::~Mouse()
{
    delete[] buttons_;
}

bool Mouse::isButtonPressed(Button button)
{
    return buttons_[static_cast<byte>(button)];
}

Vector2d Mouse::getCursorPosition()
{
    Vector2d result;
    glfwGetCursorPos(window_->window_, &result.x, &result.y);
    return result;
}

void Mouse::setCursorPosition(const Vector2d& position, Window* window)
{
    Window* tempWindow = window;
    if (window == nullptr) {
        if (window_ == nullptr) {
            return;
        }
        tempWindow = window_;
    }
    glfwSetCursorPos(tempWindow->window_, position.x, position.y);
}

void Mouse::setWindow(Window* window)
{
    window_ = window;
}
