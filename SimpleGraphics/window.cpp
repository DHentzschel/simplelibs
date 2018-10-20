#include "window.h"

#include <GLFW/glfw3.h>

#include "gfxutils.h"
#include "keycallback.h"
#include <logger.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

Window::Window()
{
    initialize();
}

Window::~Window()
{
    glfwDestroyWindow(window_);
}

bool Window::getIsRunning() const
{
    return !glfwWindowShouldClose(window_);
}

void Window::setIsRunning(const bool isRunning) const
{
    glfwSetWindowShouldClose(window_, !isRunning);
}

void Window::setKeyCallback(KeyCallback* keyCallback)
{
    glfwSetKeyCallback(window_, keyCallback->invokeCallback);
}

void Window::initialize()
{
    GfxUtils::printGlfwVersion();

    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        Logger::error("Couldn't initialize GLFW.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window_ = glfwCreateWindow(1280, 720, "Test", /*glfwGetPrimaryMonitor() <-- Fullscreen*/ nullptr, nullptr);
    if (!window_) {
        Logger::error("Couldn't create glfw window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    GLFW_KEY_UNKNOWN;

    //glfwSetKeyCallback(window_, keyCallback);

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // vsync
}

void Window::errorCallback(int errorCode, const char* description)
{
    Logger::error(description);
}
