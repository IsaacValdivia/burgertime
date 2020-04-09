#include "StaticTexture.hpp"

StaticTexture::StaticTexture(const std::string &path) {
    tex.loadFromFile(path);
}

const sf::Texture &StaticTexture::getTexture() const {
    return tex;
}
