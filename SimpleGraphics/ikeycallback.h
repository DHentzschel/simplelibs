#ifndef KEYCALLBACK_H
#define KEYCALLBACK_H

#include "inputaction.h"
#include "key.h"
#include "window.h"
#include <types.h>

class IKeyCallback {
public:
    IKeyCallback();

    ~IKeyCallback();

    void invokeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    virtual void invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods);

private:
    static bool* keys_;
};
#endif // KEYCALLBACK_H
