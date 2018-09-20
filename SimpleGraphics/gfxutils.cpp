#include "gfxutils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <logger.h>

void GfxUtils::printGlfwVersion()
{
    Logger::info(AString("GLFW ") + glfwGetVersionString());
}

void GfxUtils::printOpenGlVersion()
{
    // Todo: first initialize opengl current context
   // Logger::info((char*)glGetString(GL_VERSION));
}
