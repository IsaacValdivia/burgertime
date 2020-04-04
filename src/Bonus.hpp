#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "SpritedEntity.hpp"

#include "Constants.hpp"

class Bonus : public SpritedEntity {
private:
    static constexpr float respawn_time = 35;
    static constexpr float show_duration = 6;
    static constexpr float giving_points_duration = 6;

    static constexpr float sprite_scale = 2;

    static constexpr int ice_cream_points = 2;
    static constexpr int coffee_points = 2;
    static constexpr int fries_points = 2;

    enum State {
        HIDE,
        SHOW,
        GIVING_POINTS
    };

    State state;

    const int points;

public:
    Bonus(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const int points);

    void has_been_claimed();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool intersectsWith(const Entity &entity) const override;

    void update(float delta_t) override;
};
