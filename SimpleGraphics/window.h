#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class KeyCallback;

class Window {
public:
    Window();

    ~Window();

    bool getIsRunning() const;

    void setIsRunning(bool isRunning) const;

    void setKeyCallback(KeyCallback* keyCallback);

private:
    GLFWwindow* window_;

    KeyCallback* keyCallback_;

    void initialize();

    static void errorCallback(int errorCode, const char* description);
};

#endif // WINDOW_H
