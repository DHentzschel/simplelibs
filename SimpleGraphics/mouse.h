#ifndef MOUSE_H
#define MOUSE_H

#include <vector2d.h>

#include "key.h"

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class Window;

class Mouse {
    friend class IMouseButtonCallback;

    friend class Window;

public:
    Mouse();

    ~Mouse();

    static bool isButtonPressed(Button button);

    static Vector2d getCursorPosition();

    static void setCursorPosition(const Vector2d& position, Window* window = nullptr);

    static void setWindow(Window* window);

private:
    static bool* buttons_;

    static Mouse mouseInitializer_;

    static Window* window_;

};

#endif // MOUSE_H
