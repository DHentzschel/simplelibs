#include <pslmain.cpp>
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
    void initializeComponents() override
    {
    }

    void formMovedEvent(const Vector2& previousPosition, const Vector2& position) override
    {
        //OutputBox::information("Window moved, new position: " + TO_STRING(position.x) + ", " + TO_STRING(position.y) + "!", "Something happened!");
    }
};

void testForm()
{

    FormTest formTest;
    formTest.setSize(480, 300);
    formTest.centerToScreen();
    formTest.setWindowTitle("Test title Some umlauts: ‰ƒˆ÷¸‹ﬂ·¡‡¿‚¬È…Ë»Í ÌÕÏÃÓŒÛ”Ú“Ù‘˙⁄˘Ÿ˚€≤≥Ä@");
    formTest.show();
}

int main(int argc, char** argv)
{
    //testMessageBox();
    testForm();
    return 0;
}