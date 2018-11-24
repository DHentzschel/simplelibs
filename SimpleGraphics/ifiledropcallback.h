#ifndef IFILEDROPCALLBACK_H
#define IFILEDROPCALLBACK_H

#include <stringvector.h>

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;

class IFileDropCallback {
public:
    void invokeCallback(GLFWwindow* window, int count, const char** paths);

    virtual void invoke(GLFWwindow* window, const StringVector& paths) {}

};

#endif // IFILEDROPCALLBACK_H
