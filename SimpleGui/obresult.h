#ifndef OBRESULT_H
#define OBRESULT_H

#include <functions.h>

enum class ObResult {
    Ok = 1,
    Cancel,
    Abort,
    Retry,
    Ignore,
    Yes,
    No,
    TryAgain = 10,
    Continue
};

namespace ObResultUtils {
    inline ObResult get(int value) {
        if (value >= STATIC_CAST(int, ObResult::Ok) && value <= STATIC_CAST(int, ObResult::No) ||
            value >= STATIC_CAST(int, ObResult::TryAgain) && value <= STATIC_CAST(int, ObResult::Continue)) {
            return STATIC_CAST(ObResult, value);
        }
        return ObResult::Ok;
    }
}

#endif // OBRESULT_H
