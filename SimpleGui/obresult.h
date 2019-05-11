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
    inline ObResult get(int value)
    {
        if (value >= static_cast<int>(ObResult::Ok) && value <= static_cast<int>(ObResult::No) ||
            value >= static_cast<int>(ObResult::TryAgain) && value <= static_cast<int>(ObResult::Continue)) {
            return static_cast<ObResult>(value);
        }
        return ObResult::Ok;
    }
}

#endif // OBRESULT_H
