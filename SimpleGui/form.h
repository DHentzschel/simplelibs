#ifndef FORM_H
#define FORM_H

#include <astring.h>
#include <vector2.h>

class CloseCallback;

class FormPrivate;

class Form {
    friend class FormPrivate;
public:
    Form();

    ~Form();

    void setPosition(int x, int y);

    void centerToScreen();

    void setSize(int x, int y);

    void setIsMaximized(bool value);

    void setIsMinimized(bool value);

    void setWindowTitle(const AString& title);

    void hide();

    void show();

protected:
    // controls
    virtual void formClosedEvent() {}

    virtual void formMovedEvent(const Vector2& previousPosition, const Vector2& position) {}

    virtual void formResizedEvent(const Vector2& previousSize, const Vector2& size) {}

    virtual void initializeComponents() = 0;

private:
    FormPrivate* private_;

};

#endif // FORM_H
