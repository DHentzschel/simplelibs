#ifndef INPUTMOD_H
#define INPUTMOD_H

#include <types.h>

enum class InputMod : byte {
    Shift = 1,
    Control = 2,
    Alt = 4,
    Super = 8
};

#endif // INPUTMOD_H
