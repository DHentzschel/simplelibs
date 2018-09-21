#ifndef OUTPUTBOX_H
#define OUTPUTBOX_H

#include <astring.h>

#include "obbuttons.h"
#include "obdefaultbutton.h"
#include "obicon.h"
#include "obresult.h"

class OutputBox {
public:
    OutputBox();

    OutputBox(const AString& text, const AString& title, ObIcon icon = ObIcon::None,
        ObButtons buttons = ObButtons::Ok, ObDefaultButton defaultButton = ObDefaultButton::Button1);

    ~OutputBox() = default;

    void setText(const AString& value);

    void setTitle(const AString& value);

    void setIcon(ObIcon value);

    void setButtons(ObButtons value);

    void setDefaultButton(ObDefaultButton value);

    ObResult show();

    static ObResult error(const AString& text, const AString& title,
        ObButtons buttons = ObButtons::Ok, ObDefaultButton defaultButton = ObDefaultButton::Button1);

    static ObResult information(const AString& text, const AString& title,
        ObButtons buttons = ObButtons::Ok, ObDefaultButton defaultButton = ObDefaultButton::Button1);

    static ObResult question(const AString& text, const AString& title,
        ObButtons buttons = ObButtons::Ok, ObDefaultButton defaultButton = ObDefaultButton::Button1);

    static ObResult warning(const AString& text, const AString& title,
        ObButtons buttons = ObButtons::Ok, ObDefaultButton defaultButton = ObDefaultButton::Button1);

private:
    AString text_;

    AString title_;

    ObIcon icon_;

    ObButtons buttons_;

    ObDefaultButton defaultButton_;

};

#endif // OUTPUTBOX_H
