#include <iostream>
#include <exception>
#include "DarkGL.h"

int main(void)
{
    dark::DarkGL app;

    try {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;

}
