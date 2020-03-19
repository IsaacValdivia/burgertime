#include "StaticTexture.hpp"

StaticTexture::StaticTexture(const std::string &path) {
    tex.loadFromFile(path);
}