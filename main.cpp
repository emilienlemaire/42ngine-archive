#include <CppLogger/Log.h>
#include "src/Window.h"

int main() {
    Log::setLevel(Log::LevelDebug);
    Log::Info("Hello World");
    Window window(1000, 700, "Hello world");

    window.show();
    return 0;
}