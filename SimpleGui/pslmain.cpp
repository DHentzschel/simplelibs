#include "pprinf.h"

#include <Windows.h>

extern "C" int main(int, char **);

extern "C" int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    PrivateProcessInformation::setHInstance(hInstance);

    int argc;
    wchar_t **argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argvW == nullptr) {
        return -1;
    }

    char **argv = new char *[argc + 1];
    for (int i = 0; i < argc; ++i) {
        int length = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, argvW[i], -1, NULL, 0, NULL, NULL);
        argv[i] = new char[length + 1];
        int result = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, argvW[i], -1, argv[i], length + 1, NULL, NULL);
    }

    LocalFree(argvW);
    const int exitCode = main(argc, argv);

    for (int i = 0; i < argc && argv[i]; ++i) {
        delete[] argv[i];
    }
    delete[] argv;

    return exitCode;
}
