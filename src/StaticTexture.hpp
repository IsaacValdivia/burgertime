#pragma once

#include <SFML/Graphics.hpp>

class StaticTexture {
private:
    sf::Texture tex;

public:

    /**
     * @brief Construct a new Static Texture object
     *
     * @param path path to the texture file
     */
    StaticTexture(const std::string &path);

    /**
     * [description]
     *
     * @return const sf::Texture&
     */
    const sf::Texture &getTexture() const;
};
