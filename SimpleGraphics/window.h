#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class Window {
public:
    Window();

    ~Window();

    bool getIsRunning() const;

    void setIsRunning(bool isRunning) const;

public:
    GLFWwindow* window_;

    void initialize();

    static void errorCallback(int errorCode, const char* description);
};

#endif // WINDOW_H
