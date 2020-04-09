#pragma once

#include <cstdint>
#include <string>

class Config
{
public:
    static Config &get();

    ~Config();

    enum Resolution : uint8_t
    {
        x550x550,
        x1000x1000,
        x250x250
    };

    void set_resolution(Resolution new_resolution);

    void write_file();

    Resolution get_resolution() const;

private:
    Config();

    Config(const Config &copy);

    Config &operator=(const Config &copy);

    void create_default_config();

    const std::string file_name;
    Resolution current_resolution;
};
