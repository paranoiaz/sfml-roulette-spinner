#include "windowmanager.hpp"

int main()
{
    WindowManager windowManager;

    while (windowManager.isOpen())
    {
        windowManager.update();
        windowManager.render();
    }

    return 0;
}