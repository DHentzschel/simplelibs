#ifndef FORM_H
#define FORM_H

#include <astring.h>

class CloseCallback;

class FormPrivate;

class Form {
    friend class FormPrivate;
public:
    Form();

    ~Form();

    void setPosition(int x, int y);

    void setCenteredToScreen();

    void setSize(int x, int y);

    void setIsMaximized(bool value);

    void setIsMinimized(bool value);

    void setWindowTitle(const AString& title);

    void hide();

    void show();

    void setCloseCallback(CloseCallback* value);

private:
    FormPrivate* private_;

};

#endif // FORM_H
