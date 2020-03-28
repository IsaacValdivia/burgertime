#include "Ingredient.hpp"

Ingredient::IngredientPiece::IngredientPiece(const sf::Vector2f &_init_pos, BT_sprites::Sprite _init_sprite) :
    SpritedEntity(_init_pos, _init_sprite), stepped(false) {
    this->sprite.setScale(2, 2);
}

void Ingredient::IngredientPiece::move_down(float delta_t) {
    this->sprite.move(0, y_movement_falling * delta_t);
}

void Ingredient::IngredientPiece::move_up(float delta_t) {
    this->sprite.move(0, -y_movement_falling * delta_t);
}

void Ingredient::IngredientPiece::step() {
    stepped = true;
    this->sprite.move(0, y_movement_static);
}

bool Ingredient::IngredientPiece::isStepped() const {
    return stepped;
}

Ingredient::Ingredient(const float _x, const float _y, const char _content) :
    state(IDLE), content(_content), last_landable(NONE) {
    std::array<BT_sprites::Sprite, ING_LENGTH> sprite_indicators;

    switch (_content) {
        case TOP_BUN:
            sprite_indicators[0] = BT_sprites::Sprite::TOP_BREAD_1;
            sprite_indicators[1] = BT_sprites::Sprite::TOP_BREAD_2;
            sprite_indicators[2] = BT_sprites::Sprite::TOP_BREAD_3;
            sprite_indicators[3] = BT_sprites::Sprite::TOP_BREAD_4;
            break;

        case BOT_BUN:
            sprite_indicators[0] = BT_sprites::Sprite::BOTTOM_BREAD_1;
            sprite_indicators[1] = BT_sprites::Sprite::BOTTOM_BREAD_2;
            sprite_indicators[2] = BT_sprites::Sprite::BOTTOM_BREAD_3;
            sprite_indicators[3] = BT_sprites::Sprite::BOTTOM_BREAD_4;
            break;

        case MEAT:
            sprite_indicators[0] = BT_sprites::Sprite::BURGER_1;
            sprite_indicators[1] = BT_sprites::Sprite::BURGER_2;
            sprite_indicators[2] = BT_sprites::Sprite::BURGER_3;
            sprite_indicators[3] = BT_sprites::Sprite::BURGER_4;
            break;

        case CHEESE:
            sprite_indicators[0] = BT_sprites::Sprite::CHEESE_1;
            sprite_indicators[1] = BT_sprites::Sprite::CHEESE_2;
            sprite_indicators[2] = BT_sprites::Sprite::CHEESE_3;
            sprite_indicators[3] = BT_sprites::Sprite::CHEESE_4;
            break;

        case LETTUCE:
            sprite_indicators[0] = BT_sprites::Sprite::LETTUCE_1;
            sprite_indicators[1] = BT_sprites::Sprite::LETTUCE_2;
            sprite_indicators[2] = BT_sprites::Sprite::LETTUCE_3;
            sprite_indicators[3] = BT_sprites::Sprite::LETTUCE_4;
            break;

        case TOMATO:
            sprite_indicators[0] = BT_sprites::Sprite::TOMATO_1;
            sprite_indicators[1] = BT_sprites::Sprite::TOMATO_2;
            sprite_indicators[2] = BT_sprites::Sprite::TOMATO_3;
            sprite_indicators[3] = BT_sprites::Sprite::TOMATO_4;
            break;

        default:
            break;
    }

    const float offset_x = 16 / 2.0;
    const float offset_y = 16 / 2.0;
    for (unsigned int i = 0; i < ING_LENGTH; ++i) {
        pieces.emplace_back(sf::Vector2f(_x + offset_x + (i * 16), _y + offset_y), sprite_indicators[i]);
    }
};

void Ingredient::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &piece : pieces) {
        target.draw(piece, states);
    }
}

bool Ingredient::isFalling() {
    return state == FALLING;
}

void Ingredient::displace_middle(const float magnitude) {
    pieces[1].sprite.move(0, magnitude);
    pieces[2].sprite.move(0, magnitude);
}

void Ingredient::displace_edges(const float magnitude) {
    pieces[0].sprite.move(0, magnitude);
    pieces[3].sprite.move(0, magnitude);
}

void Ingredient::fix_position_down() {
    float lowestY = 0;

    for (auto &piece : pieces) {
        float y = piece.sprite.getPosition().y;
        if (y > lowestY) {
            lowestY = y;
        }
    }

    for (auto &piece : pieces) {
        auto position = piece.sprite.getPosition();
        piece.sprite.setPosition(position.x, lowestY);
    }
}

void Ingredient::fix_position_up() {
    float highestY = 0;

    for (auto &piece : pieces) {
        float y = piece.sprite.getPosition().y;
        if (y < highestY) {
            highestY = y;
        }
    }

    for (auto &piece : pieces) {
        auto position = piece.sprite.getPosition();
        piece.sprite.setPosition(position.x, highestY);
    }
}

void Ingredient::update(float delta_t) {
    acc_delta_t += delta_t;

    switch (state) {
        case FALLING:
            for (auto &piece : pieces) {
                piece.move_down(delta_t);
            }
            break;
        case BOUNCE_UP_1:
            if (acc_delta_t >= BOUNCE_UP_1_DURATION) {
                acc_delta_t = 0;
                state = BOUNCE_UP_2;
                displace_edges(-0.5 * y_movement_static);
                displace_middle(-2 * y_movement_static);
            }
            break;
        case BOUNCE_UP_2:
            if (acc_delta_t >= BOUNCE_UP_2_DURATION) {
                acc_delta_t = 0;
                state = FALLING;
                fix_position_down();
            }
            break;
        case BOUNCE_DOWN_1:
            if (acc_delta_t >= BOUNCE_DOWN_1_DURATION) {
                acc_delta_t = 0;
                state = BOUNCE_DOWN_2;
                displace_middle(-3 * y_movement_static);
                displace_edges(-y_movement_static);
            }
            break;
        case BOUNCE_DOWN_2:
            if (acc_delta_t >= BOUNCE_DOWN_2_DURATION) {
                acc_delta_t = 0;
                state = IDLE;
                fix_position_up();
            }
            break;
        default:
            break;
    }
}

void Ingredient::land(float y, Landable landable) {
    if (state == FALLING) {
        return;
    }

    if (landable == INGREDIENT || landable == STATIC_ING_BASKET) {
        state = BOUNCE_UP_1;
        displace_middle(-2 * y_movement_static);
        displace_edges(-y_movement_static);
    }
    else if (landable == FLOOR) {
        state = BOUNCE_DOWN_1;
        displace_edges(y_movement_static);
        displace_middle(2 * y_movement_static);
    }

    last_landable = landable;
    acc_delta_t = 0;
}

void Ingredient::drop() {
    fix_position_down();
    state = FALLING;
}

void Ingredient::stepped(const sf::FloatRect &rectangle) {
    if (state == IDLE) {

        int stepped_count = 0;

        for (int i = 0; i < ING_LENGTH; ++i) {
            if (pieces[i].getCollisionShape().intersects(rectangle) && !pieces[i].isStepped()) {
                pieces[i].step();

                // LEFT
                for (int j = i - 1; j >= 0; --j) {
                    if (pieces[j].isStepped()) {
                        pieces[j].step();
                    }
                    else {
                        break;
                    }
                }

                // RIGHT
                for (int k = i + 1; k < ING_LENGTH; k++) {
                    if (pieces[k].isStepped()) {
                        pieces[k].step();
                    }
                    else {
                        break;
                    }
                }
            }

            if (pieces[i].isStepped()) {
                ++stepped_count;
            }
        }

        if (stepped_count == ING_LENGTH) {
            fix_position_down();
            state = FALLING;
        }
    }
}

sf::FloatRect Ingredient::getCollisionShape() const {
    sf::FloatRect collisionShape = pieces[0].sprite.getGlobalBounds();
    collisionShape.width *= 4;

    // for (const auto &piece : pieces)
    // {
    //     if (piece.sprite.getGlobalBounds().top > collisionShape.top)
    //     {
    //         collisionShape.top = piece.sprite.getGlobalBounds().top;
    //     }
    // }

    return collisionShape;
}
