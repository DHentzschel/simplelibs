#ifndef MOUSE_H
#define MOUSE_H

#include <vector2.h>

#include "key.h"

class Mouse {
public:
    static bool isButtonPressed(Key key);

    static Vector2& getPosition();

private:
    Mouse();

    static bool* keys_;

    static Vector2 position_;

    static Mouse mouseInitializer_;

};

#endif // MOUSE_H
