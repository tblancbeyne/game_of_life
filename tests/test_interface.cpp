#include <iostream>

#include "Interface.hpp"

int main()
{
    std::cout << "Helloworld" << std::endl;

    gol::Matrix matrix(32, 32);

    gol::Interface interface(matrix);

    while (interface.isOpen())
    {
        interface.eventManagement();

        interface.clear();

        interface.drawMatrix();

        interface.display();

    }

}
