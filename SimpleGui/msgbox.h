#ifndef MSGBOX_H
#define MSGBOX_H

#include <astring.h>

#include "mbbuttons.h"
#include "mbdefaultbutton.h"
#include "mbicon.h"
#include "mbresult.h"

class MsgBox {
public:
    MsgBox();

    MsgBox(const AString& text, const AString& title, MbIcon icon = MbIcon::None,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    ~MsgBox() = default;

    void setText(const AString& value);

    void setTitle(const AString& value);

    void setIcon(MbIcon value);

    void setButtons(MbButtons value);

    void setDefaultButton(MbDefaultButton value);

    MbResult show();

    static MbResult error(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult information(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult question(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

    static MbResult warning(const AString& text, const AString& title,
        MbButtons buttons = MbButtons::Ok, MbDefaultButton defaultButton = MbDefaultButton::Button1);

private:
    AString text_;

    AString title_;

    MbIcon icon_;

    MbButtons buttons_;

    MbDefaultButton defaultButton_;

};

#endif // MSGBOX_H
