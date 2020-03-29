#pragma once

#include "SpritedEntity.hpp"
#include "Constants.hpp"

#include <memory>

class Map;

class Actor : public SpritedEntity {
private:
    static constexpr auto sprite_scale = 2;

protected:
    bool alive;

    Direction direction;
    Direction mirror_state;

    std::shared_ptr<Map> map;

    const BT_sprites::Sprite first_sprite;

    void mirror();
public:
    Actor(const sf::Vector2f &init_pos, const BT_sprites::Sprite init_sprite, const BT_sprites::Sprite first_sprite, std::shared_ptr<Map> map);

    sf::FloatRect getCollisionShape() const override;

    bool is_alive() const;

    virtual void die();
};
