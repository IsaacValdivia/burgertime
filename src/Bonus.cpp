#include "Bonus.hpp"

Bonus::Bonus(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const int points)
    :
    SpritedEntity(init_pos, init_sprite),
    points(points),
    state(HIDE) {
    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

void Bonus::has_been_claimed() {
    BT_sprites::update_sprite(sprite, BT_sprites::get_sprite_points(points));
}

void Bonus::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (state != HIDE) {
        target.draw(sprite, states);
    }
}

bool Bonus::intersectsWith(const Entity &entity) const {
    if (state != HIDE) {
        return getCollisionShape().intersects(entity.getCollisionShape());
    }
    return false;
}

void Bonus::update(float delta_t) {
    acc_delta_t += delta_t;

    switch (state) {
        case HIDE:
            if (acc_delta_t >= respawn_time) {
                state = SHOW;
            }
            break;
        case SHOW:
            if (acc_delta_t >= show_duration) {
                state = HIDE;
            }
        case GIVING_POINTS:
            if (acc_delta_t >= giving_points_duration) {
                state = HIDE;
            }
        default:
            break;
    }
}
