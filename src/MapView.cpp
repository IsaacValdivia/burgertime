#include "MapView.hpp"

using namespace sf;

sf::Texture MapView::floor_texture;
sf::Texture MapView::go_up_texture;
sf::Texture MapView::go_down_texture;
sf::Texture MapView::stairs_texture;

sf::RectangleShape MapView::floor(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::go_down(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::go_up(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::stairs(Vector2f(TILE_WIDTH, TILE_HEIGHT));

MapView::MapView(Map* _map) {
    floor_texture.loadFromFile("./img/floor.png");
    go_up_texture.loadFromFile("./img/go_up.png");
    go_down_texture.loadFromFile("./img/go_down.png");
    stairs_texture.loadFromFile("./img/stairs.png");

    floor.setTexture(&floor_texture);
    go_down.setTexture(&go_down_texture);
    go_up.setTexture(&go_up_texture);
    stairs.setTexture(&stairs_texture);

    map = _map;
}

int MapView::draw() {

    unsigned int dimX = 1000;
    unsigned int dimY = 1000;

    sf::Vector2f tile_size(4.0f, 4.0f);

    sf::RenderWindow window(sf::VideoMode(dimX, dimY), "Burgertime");
    //RectangleShape floor(Vector2f(TILE_DIM, TILE_DIM));

    window.clear();

    unsigned int i = -1, j;
    for (auto& row : map->data) {
        ++i;
        j = 0;
        for (auto& tile : row) {

            if (tile.isFloor()) {
                floor.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                window.draw(floor);
            }
            else if (tile.isGoUp() || tile.isGoBoth()) {
                go_up.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                window.draw(go_up);
            }
            else if (tile.isGoDown()) {
                go_down.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                window.draw(go_down);
            }
            else if (tile.isStairs()) {
                stairs.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                window.draw(stairs);
            }

            j++;
        }
    }

    window.display();


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
            //window.clear();
            //window.draw(floor);
    		//window.display();
    	}
    }

}
