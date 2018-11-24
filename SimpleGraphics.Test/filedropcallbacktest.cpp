#include "filedropcallbacktest.h"

#include <console.h>

void FileDropCallbackTest::invoke(GLFWwindow* window, const StringVector& paths)
{
    Console::print("File dropped to window, paths: ");
    for (auto& path : paths) {
        Console::print(path);
    }
}
