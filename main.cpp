#ifdef _WIN32
#include <windows.h>
#endif
#include "App.h"

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    App app;
    app.run();

    return 0;
}
