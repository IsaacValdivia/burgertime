#include "Config.hpp"
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "InputSystem.hpp"
#include <fstream>

Config::Config()
: file_name(CONFIG_FILE)
{
    std::ifstream file;
    file.open(file_name, std::ios::binary);

    if (!file)
    {
        create_default_config();
        return;
    }

    file.read(reinterpret_cast<char*>(&current_resolution), sizeof(current_resolution));
    BurgerTimeController::get().set_resolution(current_resolution);
    InputSystem::readBindings(file);
}

Config::~Config()
{
}

Config &Config::get()
{
    static Config instance;
    return instance;
}

void Config::create_default_config()
{
    current_resolution = Resolution::x550x550;
    BurgerTimeController::get().set_resolution(current_resolution);

    write_file();
}

void Config::write_file()
{
    std::ofstream file;
    file.open(file_name, std::ios::binary);

    if (!file)
    {
        // TODO: throw exception
    }

    file.write(reinterpret_cast<const char*>(&current_resolution), sizeof(current_resolution));
    InputSystem::writeBindings(file);
}

void Config::set_resolution(Resolution new_resolution)
{
    current_resolution = new_resolution;
}

Config::Resolution Config::get_resolution() const
{
    return current_resolution;
}
