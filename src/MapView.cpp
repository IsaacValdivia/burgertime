#include "MapView.hpp"

using namespace sf;

sf::Texture MapView::floor_texture;
sf::Texture MapView::go_up_texture;
sf::Texture MapView::go_down_texture;
sf::Texture MapView::stairs_texture;

sf::RectangleShape MapView::floor(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::go_down(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::go_up_left(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::go_up_right(Vector2f(TILE_WIDTH, TILE_HEIGHT));

sf::RectangleShape MapView::stairs_left(Vector2f(TILE_WIDTH, TILE_HEIGHT));
sf::RectangleShape MapView::stairs_right(Vector2f(TILE_WIDTH, TILE_HEIGHT));

MapView::MapView(Map *_map)
{
    floor_texture.loadFromFile("./img/floor.png");
    go_up_texture.loadFromFile("./img/go_up.png");
    go_down_texture.loadFromFile("./img/go_down.png");
    stairs_texture.loadFromFile("./img/stairs.png");

    floor.setTexture(&floor_texture);

    go_down.setTexture(&go_down_texture);

    go_up_left.setTexture(&go_up_texture);
    go_up_right.setTexture(&go_up_texture);

    go_up_left.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    go_up_right.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));

    stairs_left.setTexture(&stairs_texture);
    stairs_right.setTexture(&stairs_texture);

    stairs_left.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    stairs_right.setTextureRect(sf::IntRect(TILE_WIDTH, 0, TILE_WIDTH, TILE_HEIGHT));

    map = _map;
}

void MapView::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    // unsigned int dimX = 1000;
    // unsigned int dimY = 1000;

    // sf::Vector2f tile_size(4.0f, 4.0f);

    // sf::RenderWindow window(sf::VideoMode(dimX, dimY), "Burgertime");
    // RectangleShape floor(Vector2f(TILE_DIM, TILE_DIM));

    // window.clear();

    unsigned int i = 0, j;
    for (auto &row : map->data)
    {
        j = 0;
        bool double_placed = false;
        for (auto &tile : row)
        {
            if (tile.isFloor())
            {
                floor.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(floor, states);

                double_placed = false;
            }
            else if ((tile.isGoUp() || tile.isGoBoth()) && !double_placed)
            {
                go_up_left.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_up_left, states);
                go_up_right.setPosition(SIDE_MARGINS + (j+1) * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_up_right, states);

                double_placed = true;
            }
            else if (tile.isGoDown())
            {
                go_down.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(go_down, states);

                double_placed = false;
            }
            else if (tile.isStairs() && !double_placed)
            {
                stairs_left.setPosition(SIDE_MARGINS + j * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(stairs_left, states);
                stairs_right.setPosition(SIDE_MARGINS + (j+1) * TILE_WIDTH, UPPER_MARGIN + i * TILE_HEIGHT);
                target.draw(stairs_right, states);

                double_placed = true;
            }
            else {
                double_placed = false;
            }

            ++j;
        }

        ++i;
    }
}
