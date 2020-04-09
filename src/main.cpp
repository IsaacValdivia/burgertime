#include "BurgerTimeController.hpp"

#include <cstdlib>

int main(const int argc, const char **argv) {
    BurgerTimeController::get().run();

    return EXIT_SUCCESS;
}
