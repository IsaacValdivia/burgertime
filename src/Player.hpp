#include <SFML/Graphics.hpp>

#include "BT_sprites.hpp"

// TODO: REPETIR CUANDO HAYA ALGO DECIDIDO?

class Player {
public:
    static const int NUM_PLAYER_ACTIONS = 8;
    enum Action {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        PEPPER,
        DROP,
        CELEBRATE
    };
private:
    static const BT_sprites::Sprite sprite_state_machine[][NUM_PLAYER_ACTIONS];

    static const int sprite_scale = 4;
    static const int step_size = 10;

    BT_sprites::Sprite current_sprite;

    sf::Sprite player_sprite;

    Action last_direction; // LEFT, RIGHT, UP or DOWN only.
public:
    Player();

    void update(Action pa);

    sf::Sprite get_sprite() const;
};
