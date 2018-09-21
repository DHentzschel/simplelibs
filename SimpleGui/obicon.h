#ifndef OBICONS_H
#define OBICONS_H

#include <types.h>

enum class ObIcon : byte {
    None = 0x00,
    Error = 0x10,
    Question = 0x20,
    Warning = 0x30,
    Information = 0x40,
};

#endif // OBICONS_H
