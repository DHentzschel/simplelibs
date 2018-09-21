#include <pslmain.cpp>
#include <form.h>
#include <screen.h>
#include <msgbox.h>

int main(int argc, char** argv) {
    Form f;
    f.setSize(800, 800);
    f.setCenteredToScreen();
    f.setWindowTitle("Test title");
    f.show();

    return 0;
}