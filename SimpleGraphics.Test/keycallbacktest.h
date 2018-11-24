#ifndef KEYCALLBACKTEST_H
#define KEYCALLBACKTEST_H

#include <ikeycallback.h>
#include <types.h>

class KeyCallbackTest : public IKeyCallback {
public:
    KeyCallbackTest();

    ~KeyCallbackTest();

    void invoke(GLFWwindow* window, Key key, int scancode, InputAction action, byte mods) override;
};

#endif // KEYCALLBACKTEST_H
