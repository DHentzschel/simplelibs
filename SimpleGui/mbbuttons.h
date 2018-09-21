#ifndef MBBUTTONS_H
#define MBBUTTONS_H

#include <types.h>

enum class MbButtons : ushort {
    Ok = 0x0000,
    OkCancel = 0x0001,
    AbortRetryIgnore = 0x0002,
    YesNoCancel = 0x0003,
    YesNo = 0x0004,
    RetryCancel = 0x0005,
    CancelTryContinue = 0x0006,
    Help = 0x4000
};

#endif // MBBUTTONS_H
