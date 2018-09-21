#ifndef MBRESULT_H
#define MBRESULT_H

enum class MbResult {
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

namespace MbResultUtils {
    inline MbResult get(int value) {
        if (value >= STATIC_CAST(int, MbResult::Ok) && value <= STATIC_CAST(int, MbResult::No) ||
            value >= STATIC_CAST(int, MbResult::TryAgain) && value <= STATIC_CAST(int, MbResult::Continue)) {
            return STATIC_CAST(MbResult, value);
        }
        return MbResult::Ok;
    }
}

#endif // MBRESULT_H
