#include <cstdlib>

#include "BurgerTimeController.hpp"

int main(int argc, char **argv)
{
    BurgerTimeController::get().run();

    return EXIT_SUCCESS;
}
