#include "MapView.hpp"

using namespace sf;

MapView::MapView(Map* _map) {
    map = _map;

    sf::Color cyan(74, 221, 228);
    sf::Color blue(17, 8, 159);
    sf::Color grey(155, 155, 155);
}

int MapView::draw() {

    unsigned int dimX = 1000;
    unsigned int dimY = 1000;

    sf::Vector2f tile_size(4.0f, 4.0f);

    sf::RenderWindow window(sf::VideoMode(dimX, dimY), "Burgertime");

    unsigned int i = -1, j;
    for (auto& row : map->data) {
        ++i;
        for (auto& tile : row) {
            if (tile.isFloor()) {
                RectangleShape floor(Vector2f(TILE_DIM, TILE_DIM));
                floor.setPosition(0, 0);
                window.draw(floor);
            }
            //window.draw();
        }
    }


    sf::Clock deltaClock;
    while (window.isOpen()) {
    	if (deltaClock.getElapsedTime().asSeconds() >= 1.0 / 60) {
    		deltaClock.restart();
    		sf::Event event;
    		while (window.pollEvent(event)) {
    			if (event.type == sf::Event::Closed) {
    				window.close();
    			}
    		}

    		window.display();
    	}
    }

}
