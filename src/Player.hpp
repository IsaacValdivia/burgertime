#include <SFML/Graphics.hpp>

#include "BT_sprites.hpp"

#include "Actor.hpp"

// TODO: REPETIR CUANDO HAYA ALGO DECIDIDO?

class Player : public Actor {
private:
    enum Action {
        NONE,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        PEPPER,
        DROP,
        CELEBRATE,
        NUM_ACTIONS
    };

    static const BT_sprites::Sprite sprite_state_machine[][NUM_ACTIONS];

    Action last_direction; // LEFT, RIGHT, UP or DOWN only.

    Action last_action;

public:
    Player(const sf::Vector2f &init_pos);

    void update(float delta_t) override;
};
