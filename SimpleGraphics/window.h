#ifndef WINDOW_H
#define WINDOW_H

#include <vector2.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IKeyCallback;

class IMouseButtonCallback;

class IMouseScrollingCallback;

class IMouseMovingCallback;

class IFileDropCallback;

class IMouseEnterCallback;

class IResizeWindowCallback;

class IMaximizeWindowCallback;

class IMinimizeWindowCallback;

#define GL_COLOR_BUFFER_BIT 0x00004000

class Window {
    friend class Mouse;

    friend class IResizeWindowCallback;

public:
    Window();

    ~Window();

    bool getIsRunning() const;

    void setIsRunning(bool isRunning) const;

    static Vector2 getSize();

    void setKeyCallback(IKeyCallback* keyCallback);

    void setMouseButtonCallback(IMouseButtonCallback* mouseButtonCallback);

    void setMouseScrollingCallback(IMouseScrollingCallback* mouseScrollingCallback);

    void setMouseMovingCallback(IMouseMovingCallback* mouseMovingCallback);

    void setFileDropCallback(IFileDropCallback* fileDropCallback);

    void setMouseEnterCallback(IMouseEnterCallback* mouseEnterCallback);

    void setResizeWindowCallback(IResizeWindowCallback* resizeWindowCallback);

    void setMaximizeWindowCallback(IMaximizeWindowCallback* maximizeWindowCallback);

    void setMinimizeWindowCallback(IMinimizeWindowCallback* minimizeWindowCallback);

    void clear(int flags = GL_COLOR_BUFFER_BIT);

    void swapBuffers();

    void pollEvents();

private:
    GLFWwindow* window_;

    static Vector2 size_;

    static IKeyCallback* keyCallback_;

    static IMouseButtonCallback* mouseButtonCallback_;

    static IMouseScrollingCallback* mouseScrollingCallback_;

    static IMouseMovingCallback* mouseMovingCallback_;

    static IFileDropCallback* fileDropCallback_;

    static IMouseEnterCallback* mouseEnterCallback_;

    static IResizeWindowCallback* resizeWindowCallback_;

    static IMaximizeWindowCallback* maximizeWindowCallback_;

    static IMinimizeWindowCallback* minimizeWindowCallback_;

    void initialize();

    static void invokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void invokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    static void invokeMouseScollingCallback(GLFWwindow* window, double xoffset, double yoffset);

    static void invokeMouseMovingCallback(GLFWwindow* window, double xoffset, double yoffset);

    static void invokeFileDropCallback(GLFWwindow* window, int count, const char** paths);

    static void invokeMouseEnterCallback(GLFWwindow* window, int entered);

    static void invokeResizeWindowCallback(GLFWwindow* window, int width, int height);

    static void errorCallback(int errorCode, const char* description);

};

#endif // WINDOW_H
