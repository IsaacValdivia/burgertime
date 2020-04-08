#include "Config.hpp"
#include "Constants.hpp"
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
}

void Config::set_resolution(Resolution new_resolution)
{
    current_resolution = new_resolution;
}

Config::Resolution Config::get_resolution() const
{
    return current_resolution;
}
