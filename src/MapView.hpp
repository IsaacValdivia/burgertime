#pragma once

#include "Map.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * Class MapView: stores a Map, and has a callable function to draw it on the screen
 */
class MapView : public sf::Drawable {
private:
    static constexpr float TILE_WIDTH = 16.0;
    static constexpr float TILE_HEIGHT = 16.0;

    const unsigned int UPPER_MARGIN = 5 * TILE_HEIGHT;
    const unsigned int SIDE_MARGINS = 65;

    static sf::Texture floor_texture;
    static sf::Texture go_up_texture;
    static sf::Texture go_down_texture;
    static sf::Texture stairs_texture;

    static sf::RectangleShape floor;

    static sf::RectangleShape go_down;

    static sf::RectangleShape go_up_left;
    static sf::RectangleShape go_up_right;

    static sf::RectangleShape stairs_left;
    static sf::RectangleShape stairs_right;

    std::vector<Tile> player_on_tiles(const sf::Vector2f position, const sf::Vector2f scale) const;

public:

    Map* map;

    MapView(Map* _map);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool player_can_move(float &x, float &y, const sf::Sprite& player) const;
    
};
