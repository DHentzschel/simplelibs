#ifndef KEYCALLBACK_H
#define KEYCALLBACK_H
#include "window.h"
#include <avector.h>

class KeyCallback {
public:
    void invoke(GLFWwindow* window, int key, int scancode, int action, int mods) const;

private:
    static AVector<bool> keys_;
};
#endif // KEYCALLBACK_H
