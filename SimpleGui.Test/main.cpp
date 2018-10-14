#include <pslmain.cpp>
#include <keyboard.h>
#include <form.h>
#include <screen.h>
#include <outputbox.h>

void testMessageBox()
{
    /* Static functions */
    OutputBox::error("Houston we have a problem!", "A Problem!", ObButtons::RetryCancel, ObDefaultButton::Button1);
    OutputBox::information("You look good, man!", "Important fact", ObButtons::Ok);
    OutputBox::question("Are you fine?", "QOTD", ObButtons::YesNo, ObDefaultButton::Button1);
    OutputBox::warning("You may think great about these libraries.", "I warn you", ObButtons::AbortRetryIgnore, ObDefaultButton::Button3);

    /* MsgBox instances */
    OutputBox outputBox;
    outputBox.setText("I love it!");
    outputBox.setTitle("My thoughts");
    outputBox.setIcon(ObIcon::Information);
    outputBox.setButtons(ObButtons::Ok);
    outputBox.show();

    OutputBox outputBox2("If I should make another coffee.. ?", "My thoughts #2", ObIcon::Question);
    outputBox2.show();
}

class FormTest : public Form {
public:
    FormTest()
    {
        initializeComponents();
    }

private:
    virtual void formMovedEvent(const Vector2& previousPosition, const Vector2& position) override
    {
        /* Tested and should work */
        // OutputBox::information("formMovedEvent() invoked!", "Information");
    }

    virtual void formMovingEvent(const Vector2& previousPosition, const Vector2& position) override
    {
        /* Tested and should work (window size correct?) */
        // OutputBox::information("formMovingEvent() invoked!", "Information");
    }

    virtual void formResizingEvent(const Vector2& previousSize, const Vector2& size, WindowEdge windowEdge) override
    {
        /* Tested and works */
        // OutputBox::information("formResizingEvent() invoked!", "Information");
    }

    virtual void formGainedFocusEvent() override
    {
        /* Tested and works */
        // OutputBox::information("formGainedFocusEvent() invoked!", "Information");
    }

    virtual void formLostFocusEvent() override
    {
        /* Tested and works */
        // OutputBox::information("formLostFocusEvent() invoked!", "Information");
    }

    virtual void formClosedEvent() override
    {
        /* Tested and works */
        // OutputBox::information("formClosedEvent() invoked!", "Information");
    }

    virtual void formClosingEvent() override
    {
        /* Tested and works */
        // OutputBox::information("formClosingEvent() invoked!", "Information");
    }

    virtual void formShownEvent(bool isShown) override
    {
        /* Tested and works */
        // OutputBox::information("formShownEvent() invoked!", "Information");
    }

    virtual void formMaximizedEvent(const Vector2& size) override
    {
        /* Tested and works */
        // OutputBox::information("formMaximizedEvent() invoked!", "Information");
    }

    virtual void formMinimizedEvent(const Vector2& size) override
    {
        /* Tested and works */
        // OutputBox::information("formMinimizedEvent() invoked!", "Information");
    }

    virtual void formRestoredEvent(const Vector2& size) override
    {
        /* Tested and works */
        // OutputBox::information("formRestoredEvent() invoked!", "Information");
    }

    virtual void formPositionChangedEvent(const Vector2& position) override
    {
        /* Tested and works */
        // OutputBox::information("formPositionChangedEvent() invoked!", "Information");
    }

    virtual void formKeyDownEvent(Key key, ushort repeatCount, byte scanCode, bool isExtendedKey, bool wasAlreadyDown) override
    {
        /* Tested and should work */
        /* const auto text = AString("formKeyDownEvent() invoked!\nKey: %1\nRepeat count: %2\nScan code: %3\nIs extended key: %4\nwasAlreadyDown: %5")
            .arg(TO_STRING((int)key)).arg(TO_STRING(repeatCount)).arg(TO_STRING(scanCode)).arg(TO_STRING(isExtendedKey)).arg(TO_STRING(wasAlreadyDown));
        OutputBox::information(text, "Information"); */
    }

    virtual void formKeyUpEvent(Key key, ushort repeatCount, byte scanCode, bool isExtendedKey, bool wasAlreadyDown) override
    {
        /* Tested and should work */
        /* const auto text = AString("formKeyUpEvent() invoked!\nKey: %1\nRepeat count: %2\nScan code: %3\nIs extended key: %4\nwasAlreadyDown: %5")
            .arg(TO_STRING((int)key)).arg(TO_STRING(repeatCount)).arg(TO_STRING(scanCode)).arg(TO_STRING(isExtendedKey)).arg(TO_STRING(wasAlreadyDown));
        OutputBox::information(text, "Information"); */
    }

    virtual void formMouseEnteringEvent(const Vector2& position, bool inClientArea) override
    {
        /* Tested and should work */
        // OutputBox::information("formMouseEnteringEvent() invoked!", "Information");
    }

    virtual void formMouseLeavingEvent(bool inClientArea) override
    {
        /* Tested and should work */
        // const auto text = AString("formMouseLeavingEvent() invoked!\ninClientArea: %1").arg(TO_STRING(inClientArea));
        // OutputBox::information(text, "Information");
    }

    virtual void formMouseMovingEvent(const Vector2& position, bool inClientArea) override
    {
        /* Tested and works */
        // const auto text = AString("formMouseMovingEvent() invoked!\ninClientArea: %1").arg(TO_STRING(inClientArea));
        // OutputBox::information(text, "Information");
    }

    virtual void formMouseScrollingEvent(short wheelDelta, const Vector2& position) override
    {
        /* Tested and works */
        // const auto text = AString("formMouseScrollingEvent() invoked!\nWheel delta: %1\nPosition: %2, %3")
        //  .arg(TO_STRING(wheelDelta)).arg(TO_STRING(position.x)).arg(TO_STRING(position.y));
        // OutputBox::information(text, "Information");
    }

    virtual void formMouseButtonDown(Key button, const Vector2& position, bool isDoubleClick, bool inClientArea) override
    {
        /* Tested and works */
        // const auto text = AString("formMouseButtonDownEvent() invoked!\nButton: %1\nIs double click: %2\nInClientArea: %3\nPosition: %4, %5")
        //   .arg(TO_STRING((int)button)).arg(TO_STRING(isDoubleClick)).arg(TO_STRING(inClientArea))
        //   .arg(TO_STRING(position.x)).arg(TO_STRING(position.y));
        // OutputBox::information(text, "Information");
    }

    virtual void formMouseButtonUp(Key button, const Vector2& position, bool inClientArea) override
    {
        /* Tested and works */
        // const auto text = AString("formMouseButtonUpEvent() invoked!\nButton: %1\nInClientArea: %2\nPosition: %3, %4")
        //  .arg(TO_STRING((int)button)).arg(TO_STRING(inClientArea)).arg(TO_STRING(position.x)).arg(TO_STRING(position.y));
        // OutputBox::information(text, "Information");
        testSerialization();
    }

    void initializeComponents() override
    {
        SHARED_PTR(Control) control = MAKE_SHARED(Control, Control());
        addControl(control);
    }

    void testSerialization()
    {
        /* Tested and works so far, keys[i] stays true when
        key up fired while active window is OutputBox */

        // AString text;
        // for (int i = 'A'; i <= 'Z'; ++i) {
        //    text += (char)i + AString(" ") + TO_STRING_BOOL(Keyboard::isKeyPressed((Key)i)) + '\n';
        // }
        // for (int i = '0'; i <= '9'; ++i) {
        //    text += (char)i + AString(" ") + TO_STRING_BOOL((Keyboard::isKeyPressed((Key)i))) + '\n';
        // }
        // OutputBox::information(text, "Information");
    }
};

void testForm()
{
    FormTest formTest;
    formTest.setSize(480, 300);
    formTest.centerToScreen();
    formTest.setWindowTitle("Test title Some umlauts: äÄöÖüÜßáÁàÀâÂéÉèÈêÊíÍìÌîÎóÓòÒôÔúÚùÙûÛ²³€@");
    formTest.show();
}

int main(int argc, char** argv)
{
    // testMessageBox();
    testForm();
    return 0;
}