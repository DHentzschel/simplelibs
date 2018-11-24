#include "ifiledropcallback.h"

void IFileDropCallback::invokeCallback(GLFWwindow* window, int count, const char** paths)
{
    StringVector pathList;
    pathList.reserve(count);

    for (auto i = 0; i < count; ++i) {
        pathList.append(paths[i]);
    }

    invoke(window, pathList);
}
