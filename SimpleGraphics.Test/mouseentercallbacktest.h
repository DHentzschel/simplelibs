#ifndef MOUSEENTERCALLBACKTEST_H
#define MOUSEENTERCALLBACKTEST_H

#include <imouseentercallback.h>

class MouseEnterCallbackTest : public IMouseEnterCallback {
public:
    void invoke(GLFWwindow* window, bool entered) override;

};

#endif // MOUSEENTERCALLBACKTEST_H
