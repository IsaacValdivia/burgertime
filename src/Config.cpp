#include "Config.hpp"

#include "BurgerTimeController.hpp"
#include "Constants.hpp"
#include "InputSystem.hpp"
#include "Audio.hpp"

#include <fstream>

Config::Config()
    : file_name(CONFIG_FILE) {
    std::ifstream file;
    file.open(file_name, std::ios::binary);

    if (!file) {
        create_default_config();
        return;
    }

    file.read(reinterpret_cast<char *>(&current_resolution.x), sizeof(current_resolution.x));
    file.read(reinterpret_cast<char *>(&current_resolution.y), sizeof(current_resolution.y));
    file.read(reinterpret_cast<char *>(&are_borders_on), sizeof(are_borders_on));
    file.read(reinterpret_cast<char *>(&sfx_vol), sizeof(sfx_vol));
    file.read(reinterpret_cast<char *>(&music_vol), sizeof(music_vol));
    BurgerTimeController::get().set_resolution(current_resolution);
    Audio::set_sfx_vol(sfx_vol);
    Audio::set_music_vol(music_vol);
    InputSystem::read_bindings(file);
}

Config::~Config() {
}

Config &Config::get() {
    static Config instance;
    return instance;
}

void Config::create_default_config() {
    auto &controller = BurgerTimeController::get();
    current_resolution = controller.get_available_resolutions()[controller.get_available_resolutions().size() - 1];
    sfx_vol = 100;
    music_vol = 100;
    are_borders_on = true;
    controller.set_resolution(current_resolution);
    Audio::set_sfx_vol(sfx_vol);
    Audio::set_music_vol(music_vol);

    write_file();
}

void Config::write_file() {
    std::ofstream file;
    file.open(file_name, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Could not write a configuration file");
    }

    file.write(reinterpret_cast<const char *>(&current_resolution.x), sizeof(current_resolution.x));
    file.write(reinterpret_cast<const char *>(&current_resolution.y), sizeof(current_resolution.y));
    file.write(reinterpret_cast<const char *>(&are_borders_on), sizeof(are_borders_on));
    file.write(reinterpret_cast<const char *>(&sfx_vol), sizeof(sfx_vol));
    file.write(reinterpret_cast<const char *>(&music_vol), sizeof(music_vol));
    InputSystem::write_bindings(file);
}

void Config::set_resolution(sf::Vector2u new_resolution) {
    current_resolution = new_resolution;
}

void Config::set_sfx_vol(unsigned int new_sfx_vol) {
    sfx_vol = new_sfx_vol;
}

void Config::set_music_vol(unsigned int new_music_vol) {
    music_vol = new_music_vol;
}

void Config::change_border_mode() {
    are_borders_on = !are_borders_on;
}

sf::Vector2u Config::get_resolution() const {
    return current_resolution;
}

unsigned int Config::get_sfx_volume() const {
    return sfx_vol;
}

unsigned int Config::get_music_volume() const {
    return music_vol;
}

bool Config::get_are_borders_on() const {
    return are_borders_on;
}
