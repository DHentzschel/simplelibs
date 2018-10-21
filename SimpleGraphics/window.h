#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IKeyCallback;

class Window {
public:
    Window();

    ~Window();

    bool getIsRunning() const;

    void setIsRunning(bool isRunning) const;

    void setKeyCallback(IKeyCallback* keyCallback);

    void swapBuffers();

    void pollEvents();

private:
    GLFWwindow* window_;

    static IKeyCallback* keyCallback_;

    void initialize();

    static void invokeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void errorCallback(int errorCode, const char* description);
};

#endif // WINDOW_H
