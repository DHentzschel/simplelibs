#ifndef MSGBOX_H
#define MSGBOX_H

#include <astring.h>

#include "mbbuttons.h"
#include "mbdefaultbutton.h"
#include "mbresult.h"

class MsgBox {
public:
    MsgBox();

    ~MsgBox();

    static MbResult error(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult information(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult question(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult warning(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);
};

#endif // MSGBOX_H
