#include "StaticTexture.hpp"

StaticTexture::StaticTexture(std::string path) {
    sf::Texture tex;
    tex.loadFromFile(path);
}