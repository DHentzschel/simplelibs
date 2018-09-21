#include <pslmain.cpp>
#include <form.h>
#include <screen.h>
#include <msgbox.h>

void testMessageBox()
{
    /* Static functions */
    MsgBox::error("Houston we have a problem!", "A Problem!", MbButtons::RetryCancel, MbDefaultButton::Button1);
    MsgBox::information("You look good, man!", "Important fact", MbButtons::Ok);
    MsgBox::question("Are you fine?", "QOTD", MbButtons::YesNo, MbDefaultButton::Button1);
    MsgBox::warning("You may think great about these libraries.", "I warn you", MbButtons::AbortRetryIgnore, MbDefaultButton::Button3);

    /* MsgBox instances */
    MsgBox msgBox;
    msgBox.setText("I love it!");
    msgBox.setTitle("My thoughts");
    msgBox.setIcon(MbIcon::Information);
    msgBox.setButtons(MbButtons::Ok);
    msgBox.show();

    MsgBox msgBox2("If I should make another coffee.. ?", "My thoughts #2", MbIcon::Question);
    msgBox2.show();
}

int main(int argc, char** argv)
{
    testMessageBox();

    Form f;
    f.setSize(800, 800);
    f.setCenteredToScreen();
    f.setWindowTitle("Test title");
    f.show();

    return 0;
}