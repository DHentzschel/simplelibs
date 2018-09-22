#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "form.h"

class Keyboard {
public:
    static bool isKeyPressed(Key key);

    static const bool* getKeyArray();

private:
    Keyboard();

    ~Keyboard();

    static bool* keys_;

    static Keyboard keyboardInitializer_;
};

#endif // KEYBOARD_H
