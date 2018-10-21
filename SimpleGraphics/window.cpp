#include "window.h"

#include <GLFW/glfw3.h>

#include "gfxutils.h"
#include "ikeycallback.h"
#include <logger.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

IKeyCallback* Window::keyCallback_ = nullptr;

Window::Window()
{
    initialize();
}

Window::~Window()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
}

bool Window::getIsRunning() const
{
    return !glfwWindowShouldClose(window_);
}

void Window::setIsRunning(const bool isRunning) const
{
    glfwSetWindowShouldClose(window_, !isRunning);
}

void Window::invokeCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (keyCallback_ != nullptr) {
        keyCallback_->invokeCallback(window, key, scancode, action, mods);
    }
}

void Window::setKeyCallback(IKeyCallback* keyCallback)
{
    keyCallback_ = keyCallback;
    glfwSetKeyCallback(window_, invokeCallback);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window_);
}

void Window::pollEvents()
{
    glfwPollEvents();
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
    if (window_ == nullptr) {
        Logger::error("Couldn't create glfw window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // vsync
}

void Window::errorCallback(int errorCode, const char* description)
{
    Logger::error(description);
}
