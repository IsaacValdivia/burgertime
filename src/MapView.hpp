#include "Map.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

/**
 * Class MapView: stores a Map, and has a callable function to draw it on the screen
 */
class MapView {
private:
    const float TILE_DIM = 4.0;
    const unsigned int UPPER_MARGIN = 20;
    const unsigned int SIDE_MARGINS = 4;

    static const sf::Color blue;
    static const sf::Color cyan;
    static const sf::Color grey;

public:

    Map* map;

    MapView(Map* _map);

    int draw();
    
};
