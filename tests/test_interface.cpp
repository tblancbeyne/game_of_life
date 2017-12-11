#include <iostream>

#include "Interface.hpp"

int main()
{
    std::cout << "Helloworld" << std::endl;

    gol::Matrix matrix(100, 100);

    gol::Interface interface(matrix);

    while (interface.isOpen())
    {
        interface.eventManagement();

        interface.clear();

        if (interface.isRunning())
        {
            interface.update();
        }

        interface.drawMatrix();

        interface.display();

    }

}
