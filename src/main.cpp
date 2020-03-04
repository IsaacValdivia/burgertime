#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "BurgerTimeController.hpp"

int main(int argc, char **argv)
{
    BurgerTimeController::get().run();

    return EXIT_SUCCESS;
}
