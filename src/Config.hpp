#pragma once

#include <cstdint>
#include <string>

class Config {
public:
    enum Resolution : uint8_t {
        x550x550,
        x1000x1000,
        x250x250
    };

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
    Resolution current_resolution;

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
    void set_resolution(Resolution new_resolution);

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
    Resolution get_resolution() const;
};
