#pragma once

#include <SFML/System.hpp>
#include <cstdint>
#include <string>

class Config {
private:
    /**
     * @brief Construct a new Config object
     *
     */
    Config();

    /**
     * @brief Construct a new Config object
     *
     * @param copy
     */
    Config(const Config &copy);

    /**
     * @brief = operator for config
     *
     * @param copy
     * @return Config&
     */
    Config &operator=(const Config &copy);

    /**
     * @brief Create a default config object
     *
     */
    void create_default_config();

    const std::string file_name;
    sf::Vector2u current_resolution;
    bool are_borders_on;
    unsigned int sfx_vol;
    unsigned int music_vol;

public:
    /**
     * @brief Returns Config singleton
     *
     * @return Config&
     */
    static Config &get();

    /**
     * @brief Destroy the Config object
     *
     */
    ~Config();

    /**
     * @brief Sets the resolution to new_resolution
     *
     * @param new_resolution
     */
    void set_resolution(sf::Vector2u new_resolution);

    /**
     * @brief Sets the sfx volume to new_sfx_vol
     *
     * @param new_sfx_vol
     */
    void set_sfx_vol(unsigned int new_sfx_vol);

    /**
     * @brief Sets the music volume to new_music_vol
     *
     * @param new_music_vol
     */
    void set_music_vol(unsigned int new_music_vol);

    /**
     * @brief Changes the border mode
     */
    void change_border_mode();

    /**
     * @brief Writes to config file
     *
     */
    void write_file();

    /**
     * @brief Gets the resolution object
     *
     * @return Resolution
     */
    sf::Vector2u get_resolution() const;

    /**
     * @brief Gets the sfx volume
     *
     * @return unsigned int
     */
    unsigned int get_sfx_volume() const;

    /**
     * @brief Gets the music volume
     *
     * @return unsigned int
     */
    unsigned int get_music_volume() const;

    /**
     * @brief Checks if the borders are set or not
     *
     * @return bool
     */
    bool get_are_borders_on() const;
};
