#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "key.h"

class Keyboard {
    friend class IKeyCallback;

public:
    Keyboard();

    ~Keyboard();

    bool isKeyPressed(Key key) const;

private:
    static bool* keys_;

    static Keyboard keyboardInitializer;

    static const auto arraySize_ = 32'767;

};

#endif // KEYBOARD_H
