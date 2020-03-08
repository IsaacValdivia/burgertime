#include "Map.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * Class MapView: stores a Map, and has a callable function to draw it on the screen
 */
class MapView {
private:
    static constexpr float TILE_WIDTH = 52.0;
    static constexpr float TILE_HEIGHT = 28.0;
    const unsigned int UPPER_MARGIN = 5 * TILE_HEIGHT;
    const unsigned int SIDE_MARGINS = TILE_WIDTH;

    static sf::Texture floor_texture;
    static sf::Texture go_up_texture;
    static sf::Texture go_down_texture;
    static sf::Texture stairs_texture;

    static sf::RectangleShape floor;
    static sf::RectangleShape go_down;
    static sf::RectangleShape go_up;
    static sf::RectangleShape stairs;

public:

    Map* map;

    MapView(Map* _map);

    int draw();
    
};
