#ifndef MOUSE_H
#define MOUSE_H

#include <vector2i.h>

#include "key.h"

class Mouse {
public:
    static bool isButtonPressed(Key key);

    static Vector2i& getPosition();

private:
    Mouse();

    static bool* keys_;

    static Vector2i position_;

    static Mouse mouseInitializer_;

};

#endif // MOUSE_H
