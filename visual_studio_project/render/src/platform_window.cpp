#include "platform_window.h"
#include "win32_window.h"


namespace platform
{
    window* window::load()
    {
        return new win32_window();
    }
}
