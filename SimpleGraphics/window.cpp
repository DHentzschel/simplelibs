#include "window.h"

#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <logger.h>

#include "gfxutils.h"
#include "ikeycallback.h"
#include "imousebuttoncallback.h"
#include "imousescrollingcallback.h"
#include "imousemovingcallback.h"
#include "ifiledropcallback.h"
#include "imouseentercallback.h"
#include "iresizewindowcallback.h"

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

Vector2 Window::size_;

IKeyCallback* Window::keyCallback_ = nullptr;

IMouseButtonCallback* Window::mouseButtonCallback_ = nullptr;

IMouseScrollingCallback* Window::mouseScrollingCallback_ = nullptr;

IMouseMovingCallback* Window::mouseMovingCallback_ = nullptr;

IFileDropCallback* Window::fileDropCallback_ = nullptr;

IMouseEnterCallback* Window::mouseEnterCallback_ = nullptr;

IResizeWindowCallback* Window::resizeWindowCallback_ = nullptr;

IMaximizeWindowCallback* Window::maximizeWindowCallback_ = nullptr;

IMinimizeWindowCallback* Window::minimizeWindowCallback_ = nullptr;
static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};
static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

GLuint vertex_buffer, vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location;

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

Vector2 Window::getSize()
{
    return size_;
}

void Window::invokeKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (keyCallback_ != nullptr) {
        keyCallback_->invokeCallback(window, key, scancode, action, mods);
    }
}

void Window::invokeMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (mouseButtonCallback_ != nullptr) {
        mouseButtonCallback_->invokeCallback(window, button, action, mods);
    }
}

void Window::invokeMouseScollingCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (mouseScrollingCallback_ != nullptr) {
        mouseScrollingCallback_->invokeCallback(window, Vector2d(xoffset, yoffset));
    }
}

void Window::invokeMouseMovingCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (mouseMovingCallback_ != nullptr) {
        mouseMovingCallback_->invokeCallback(window, Vector2d(xoffset, yoffset));
    }
}

void Window::invokeFileDropCallback(GLFWwindow* window, int count, const char** paths)
{
    if (fileDropCallback_ != nullptr) {
        fileDropCallback_->invokeCallback(window, count, paths);
    }
}

void Window::invokeMouseEnterCallback(GLFWwindow* window, int entered)
{
    if (mouseEnterCallback_ != nullptr) {
        mouseEnterCallback_->invokeCallback(window, entered);
    }
}

void Window::invokeResizeWindowCallback(GLFWwindow* window, int width, int height)
{
    if (resizeWindowCallback_ != nullptr) {
        resizeWindowCallback_->invokeCallback(window, width, height);
    }
}

void Window::setKeyCallback(IKeyCallback* keyCallback)
{
    keyCallback_ = keyCallback;
    glfwSetKeyCallback(window_, invokeKeyCallback);
}

void Window::setMouseButtonCallback(IMouseButtonCallback* mouseButtonCallback)
{
    mouseButtonCallback_ = mouseButtonCallback;
    glfwSetMouseButtonCallback(window_, invokeMouseButtonCallback);
}

void Window::setMouseScrollingCallback(IMouseScrollingCallback* mouseScrollingCallback)
{
    mouseScrollingCallback_ = mouseScrollingCallback;
    glfwSetScrollCallback(window_, invokeMouseScollingCallback);
}

void Window::setMouseMovingCallback(IMouseMovingCallback* mouseMovingCallback)
{
    mouseMovingCallback_ = mouseMovingCallback;
    glfwSetCursorPosCallback(window_, invokeMouseMovingCallback);
}

void Window::setFileDropCallback(IFileDropCallback* fileDropCallback)
{
    fileDropCallback_ = fileDropCallback;
    glfwSetDropCallback(window_, invokeFileDropCallback);
}

void Window::setMouseEnterCallback(IMouseEnterCallback* mouseEnterCallback)
{
    mouseEnterCallback_ = mouseEnterCallback;
    glfwSetCursorEnterCallback(window_, invokeMouseEnterCallback);
}

void Window::setResizeWindowCallback(IResizeWindowCallback* resizeWindowCallback)
{
    resizeWindowCallback_ = resizeWindowCallback;
    if (maximizeWindowCallback_ != nullptr) {
        resizeWindowCallback_->maximizeWindowCallback_ = maximizeWindowCallback_;
    }
    if (minimizeWindowCallback_ != nullptr) {
        resizeWindowCallback_->minimizeWindowCallback_ = minimizeWindowCallback_;
    }

    glfwSetWindowSizeCallback(window_, invokeResizeWindowCallback);
}

void Window::setMaximizeWindowCallback(IMaximizeWindowCallback* maximizeWindowCallback)
{
    maximizeWindowCallback_ = maximizeWindowCallback;
    if (resizeWindowCallback_ != nullptr) {
        resizeWindowCallback_->maximizeWindowCallback_ = maximizeWindowCallback_;
    }
}

void Window::setMinimizeWindowCallback(IMinimizeWindowCallback* minimizeWindowCallback)
{
    minimizeWindowCallback_ = minimizeWindowCallback;
    if (resizeWindowCallback_ != nullptr) {
        resizeWindowCallback_->minimizeWindowCallback_ = minimizeWindowCallback_;
    }
}

void Window::clear(int flags)
{
    glClear(flags);
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

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
        sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(float) * 5, (void*)(sizeof(float) * 2));
}

void Window::errorCallback(int errorCode, const char* description)
{
    Logger::error(description);
}
