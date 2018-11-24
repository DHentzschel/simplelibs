#ifndef IKEYCALLBACK_H
#define IKEYCALLBACK_H

#include <types.h>

#include "inputaction.h"
#include "key.h"

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IKeyCallback {
public:
    void invokeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    virtual void invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods) {}

};
#endif // IKEYCALLBACK_H
