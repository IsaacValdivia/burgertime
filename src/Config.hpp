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

    Resolution get_resolution() const;

private:
    Config();

    void create_default_config();

    const std::string file_name;
    Resolution current_resolution;
};
