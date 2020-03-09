#include "BT_sprites.hpp"

#include <SFML/Graphics.hpp>

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "Demo Game");
    // window.setKeyRepeatEnabled(false);


    // sf::Texture back_texture;
    // if (!back_texture.loadFromFile("img/stairs.png")) {
    //     fprintf(stderr, "HAAAYDYWADAWDA");
    // }

    // background.setTexture(back_texture);
    // background.setScale(sf::Vector2f(500, 500));
    // background.setPosition(80, 80);

    sf::Sprite sprite;
    sf::Sprite background;

    sf::Clock clock;

    BT_sprites::set_initial_sprite(sprite, BT_sprites::Sprite(0));
    BT_sprites::set_initial_sprite(background, BT_sprites::Sprite(0));
    sprite.setScale(sf::Vector2f(10, 10));
    background.setScale(sf::Vector2f(50, 50));

    sprite.setPosition(220, 200);
    background.setPosition(0, 80);

    int iter = 0;

    //Game Loop
    sf::Clock fps_clock;
    while (window.isOpen()) {
        if (fps_clock.getElapsedTime().asSeconds() >= 1.0 / 10) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                BT_sprites::update_sprite(sprite, (BT_sprites::Sprite)iter++);
            }

            window.clear(); //Clear Window

            window.draw(background);
            window.draw(sprite); //Draw Player Sprite
            window.display(); //Display Window
            fps_clock.restart();
        }
    }

    return 0;
}
