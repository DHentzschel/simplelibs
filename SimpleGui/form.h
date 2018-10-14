#ifndef FORM_H
#define FORM_H

#include <astring.h>
#include <vector2.h>

#include "control.h"
#include "key.h"
#include "windowedge.h"

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

    void addControl(SHARED_PTR(Control) control);

protected:
    virtual void formMovedEvent(const Vector2& previousPosition, const Vector2& position) {}

    virtual void formMovingEvent(const Vector2& previousPosition, const Vector2& position) {}

    virtual void formResizingEvent(const Vector2& previousSize, const Vector2& size, WindowEdge windowEdge) {}

    virtual void formGainedFocusEvent() {}

    virtual void formLostFocusEvent() {}

    virtual void formClosedEvent() {}

    virtual void formClosingEvent() {}

    virtual void formShownEvent(bool isShown) {}

    virtual void formMaximizedEvent(const Vector2& size) {}

    virtual void formMinimizedEvent(const Vector2& size) {}

    virtual void formRestoredEvent(const Vector2& size) {}

    virtual void formPositionChangedEvent(const Vector2& position) {}

    virtual void formKeyDownEvent(Key key, ushort repeatCount, byte scanCode, bool isExtendedKey, bool wasAlreadyDown) {}

    virtual void formKeyUpEvent(Key key, ushort repeatCount, byte scanCode, bool isExtendedKey, bool wasAlreadyDown) {}

    virtual void formMouseEnteringEvent(const Vector2& position, bool inClientArea) {}

    virtual void formMouseLeavingEvent(bool inClientArea) {}

    virtual void formMouseMovingEvent(const Vector2& position, bool inClientArea) {}

    virtual void formMouseScrollingEvent(short wheelDelta, const Vector2& position) {}

    virtual void formMouseButtonDown(Key button, const Vector2& position, bool isDoubleClick, bool inClientArea) {}

    virtual void formMouseButtonUp(Key button, const Vector2& position, bool inClientArea) {}

    virtual void initializeComponents() = 0;

private:
    FormPrivate* private_;

};

#endif // FORM_H
