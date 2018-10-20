#include "../SimpleGraphics/window.h"
#include "../SimpleGraphics/keycallback.h"

int main()
{
    Window window;
    window.setIsRunning(true);
    KeyCallback keycb;
    window.setKeyCallback(&keycb);

    while (window.getIsRunning()) {

    }

    return 0;
}