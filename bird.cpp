#include "Window.h"

#include <time.h>

int main(void) {
    srand( (unsigned int)time(NULL) );
    Window w;
    w.MainLoop();
    return 0;
}
