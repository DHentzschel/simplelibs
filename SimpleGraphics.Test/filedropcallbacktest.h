#ifndef FILEDROPCALLBACKTEST_H
#define FILEDROPCALLBACKTEST_H

#include <ifiledropcallback.h>

class FileDropCallbackTest : public IFileDropCallback {
public:
    void invoke(GLFWwindow* window, const StringVector& paths);

};

#endif // FILEDROPCALLBACKTEST_H
