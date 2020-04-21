#include "Bonus.hpp"

#include "Audio.hpp"

Bonus::Bonus(const sf::Vector2f &init_pos, const BtSprites::Sprite init_sprite,
             const int points)
    :
    SpritedEntity(init_pos, init_sprite),
    points(points),
    state(HIDE),
    initial_sprite(init_sprite), remaining_respawns(max_respawns) {
    sprite.setScale(sf::Vector2f(sprite_scale, sprite_scale));
}

void Bonus::has_been_claimed() {
    state = GIVING_POINTS;
    acc_delta_t = 0;

    Audio::play(Audio::Track::PEPPER_UP);

    BtSprites::update_sprite(sprite, BtSprites::get_sprite_points(points));
}

void Bonus::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (state != HIDE) {
        target.draw(sprite, states);
    }
}

bool Bonus::intersects_with(const Entity &entity) const {
    if (state == SHOW) {
        return get_collision_shape().intersects(entity.get_collision_shape());
    }
    return false;
}

int Bonus::get_points() const {
    return points;
}

void Bonus::update(const float delta_t) {
    acc_delta_t += delta_t;

    switch (state) {
        case HIDE:
            if (acc_delta_t >= respawn_time) {
                if (remaining_respawns == 0) {
                    return;
                }

                state = SHOW;

                remaining_respawns--;

                Audio::play(Audio::Track::NEW_INGREDIENT);

                acc_delta_t = 0;
            }
            break;
        case SHOW:
            if (acc_delta_t >= show_duration) {
                state = HIDE;

                acc_delta_t = 0;
            }
            break;
        case GIVING_POINTS:
            if (acc_delta_t >= giving_points_duration) {
                state = HIDE;

                BtSprites::update_sprite(sprite, initial_sprite);

                acc_delta_t = 0;
            }
            break;
        default:
            break;
    }
}
