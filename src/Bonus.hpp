#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "BT_sprites.hpp"
#include "SpritedEntity.hpp"

#include "Constants.hpp"

class Bonus : public SpritedEntity {
private:
    static constexpr float respawn_time = 37;
    static constexpr float show_duration = 7;
    static constexpr float giving_points_duration = 1;

    static constexpr float sprite_scale = 2;

    enum State {
        HIDE,
        SHOW,
        GIVING_POINTS
    };

    const BT_sprites::Sprite initial_sprite;

    State state;

    const int points;

public:
    Bonus(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const int points);

    void has_been_claimed();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool intersectsWith(const Entity &entity) const override;

    void update(float delta_t) override;

    int get_points() const;
};
