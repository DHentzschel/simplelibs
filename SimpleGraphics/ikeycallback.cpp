#include "ikeycallback.h"

#include <memory>
#include <GLFW/glfw3.h>

#include <functions.h>

bool* IKeyCallback::keys_ = nullptr;

IKeyCallback::IKeyCallback()
{
    if (keys_ == nullptr) {
        keys_ = new bool[200'000];
        memset(keys_, false, 200'000);
    }
}

IKeyCallback::~IKeyCallback()
{
    delete[] keys_;
}

void IKeyCallback::invokeCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
    keys_[key] = action == GLFW_PRESS;
    invoke(window, STATIC_CAST(Key, key), scancode, STATIC_CAST(InputAction, action), STATIC_CAST(byte, mods));
}

void IKeyCallback::invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods)
{
}

