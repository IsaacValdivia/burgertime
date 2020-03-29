#include "Ingredient.hpp"

Ingredient::IngredientPiece::IngredientPiece(const sf::Vector2f &_init_pos, BT_sprites::Sprite _init_sprite) :
    SpritedEntity(_init_pos, _init_sprite), stepped(false) {
    this->sprite.setScale(2, 2);
}

void Ingredient::IngredientPiece::move_y(float magnitude) {
    this->sprite.move(0, magnitude);
}

void Ingredient::IngredientPiece::step() {
    stepped = true;
    this->sprite.move(0, y_movement_static);
}

bool Ingredient::IngredientPiece::isStepped() const {
    return stepped;
}

Ingredient::Ingredient(const float _x, const float _y, const char _content) :
    state(IDLE), content(_content), last_landable(NONE), num_levels(1), staticTested(false) {
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
}

Ingredient::Ingredient(Ingredient && other) noexcept :
    state(other.state), content(other.content), last_landable(other.last_landable), num_levels(other.num_levels), 
    staticTested(other.staticTested), ingredient_moved(std::move(other.ingredient_moved)),
    ingredient_stopped_moving(std::move(other.ingredient_stopped_moving)), pieces(std::move(other.pieces))
{

}

void Ingredient::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &piece : pieces) {
        target.draw(piece, states);
    }

#if false
    auto collisionShape = getCollisionShape();
    sf::RectangleShape drawShape;
    drawShape.setOutlineColor(sf::Color::Red);
    drawShape.setFillColor(sf::Color::Transparent);
    drawShape.setOutlineThickness(1);
    drawShape.setPosition(collisionShape.left, collisionShape.top);
    drawShape.setSize(sf::Vector2f(collisionShape.width, collisionShape.height));
    target.draw(drawShape, states);
#endif
}

bool Ingredient::isStatic() const {
    return state == STATIC;
}

bool Ingredient::isIdle() const {
    return state == IDLE;
}

bool Ingredient::isFalling() const {
    return state == FALLING;
}

bool Ingredient::isBouncing() const {
    return state == BOUNCE_UP_1 ||
        state == BOUNCE_UP_2 ||
        state == BOUNCE_UP_3 ||
        state == BOUNCE_DOWN_1 ||
        state == BOUNCE_DOWN_2 ||
        state == BOUNCE_DOWN_3;    
}

void Ingredient::displace_middle(const float magnitude) {
    pieces[1].sprite.move(0, magnitude);
    pieces[2].sprite.move(0, magnitude);

    ingredient_moved(pieces[1].sprite.getPosition().y - 13);
}

void Ingredient::displace_edges(const float magnitude) {
    pieces[0].sprite.move(0, magnitude);
    pieces[3].sprite.move(0, magnitude);
}

void Ingredient::fix_to_y(const float y) {
    for (auto &piece : pieces) {
        piece.sprite.setPosition(piece.sprite.getPosition().x, y);
    }
}

void Ingredient::move_down(const float delta_t) {
    float mov = y_movement_falling * delta_t;
    for (auto &piece : pieces) {
        piece.move_y(mov);
    }

    ingredient_moved(pieces[1].sprite.getPosition().y - 13);
}

void Ingredient::move_down_no_delta(const float magnitude) {
    for (auto &piece : pieces) {
        piece.sprite.move(0, magnitude);
    }
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
    float highestY = pieces[0].sprite.getPosition().y;

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

void Ingredient::descend_and_check() {
    --num_levels;
    if (num_levels > 0) {
        drop();
    }
    else {
        if (last_landable == STATIC_ING_BASKET) {
            state = STATIC;
        }
        else {
            state = IDLE;
        }
        ingredient_stopped_moving();
    }
}

void Ingredient::update(float delta_t) {
    acc_delta_t += delta_t;

    switch (state) {
        case FALLING:
            move_down(delta_t);
            break;
        case BOUNCE_UP_1:
            if (acc_delta_t >= BOUNCE_DURATION) {
                state = BOUNCE_UP_2;

                acc_delta_t = 0;
                displace_middle(-1 * bounce_movement);
                displace_edges(-1.5 * bounce_movement);
            }
            break;
        case BOUNCE_UP_2:
            if (acc_delta_t >= BOUNCE_DURATION) {
                state = BOUNCE_UP_3;

                acc_delta_t = 0;
                displace_edges(-2 * bounce_movement);
                displace_middle(-3 * bounce_movement);
            }
            break;
        case BOUNCE_UP_3:
            if (acc_delta_t >= BOUNCE_DURATION) {
                state = FALLING;

                acc_delta_t = 0;
                fix_position_down();
            }
            break;
        case BOUNCE_DOWN_1:
            if (acc_delta_t >= BOUNCE_DURATION) {
                state = BOUNCE_DOWN_2;

                acc_delta_t = 0;

                displace_edges(1 * bounce_movement);
                displace_middle(1.5 * bounce_movement);
            }
            break;
        case BOUNCE_DOWN_2:
            if (acc_delta_t >= BOUNCE_DURATION) {
                state = BOUNCE_DOWN_3;

                acc_delta_t = 0;

                displace_middle(-2.0 * bounce_movement);
                displace_edges(-1 * bounce_movement);
            }
            break;
        case BOUNCE_DOWN_3:
            if (acc_delta_t >= BOUNCE_DURATION) {
                descend_and_check();

                acc_delta_t = 0;

                fix_position_down();
            }
        case IDLE:
            last_landable = NONE;
            break;
    }
}

bool Ingredient::testStatic() {
    if (state == STATIC && !staticTested) {
        staticTested = true;

        return true;
    }
    return false;
}

void Ingredient::resetSteps() {
    for (auto& piece : pieces) {
        piece.stepped = false;
    }
}

void Ingredient::land(float y, Landable landable) {
    if (pieces[0].sprite.getPosition().y >= y - 6) {
        fix_to_y(y);

        if (landable == last_landable) {
            descend_and_check();

            return;
        }

        if (landable == INGREDIENT || landable == STATIC_ING_BASKET) {
            state = BOUNCE_UP_1;
        }
        else if (landable == FLOOR) {
            state = BOUNCE_DOWN_1;
        }

        last_landable = landable;
        acc_delta_t = 0;
    }
}

void Ingredient::drop() {
    fix_position_down();
    
    move_down_no_delta(1);
    resetSteps();
    state = FALLING;
}

bool Ingredient::stepped(const sf::FloatRect &rectangle, const int _num_levels) {
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
            num_levels = _num_levels;
            drop();

            return true;
        }
    }
    
    return false;
}

sf::FloatRect Ingredient::getCollisionShape() const {
    sf::FloatRect collisionShape = pieces[0].sprite.getGlobalBounds();
    collisionShape.width *= 4;
    // collisionShape.height -= 13;

    // for (const auto &piece : pieces)
    // {
    //     if (piece.sprite.getGlobalBounds().top > collisionShape.top)
    //     {
    //         collisionShape.top = piece.sprite.getGlobalBounds().top;
    //     }
    // }

    return collisionShape;
}

std::pair<nod::connection, nod::connection> Ingredient::connect_enemy_surfer(const std::function<void(float)> &enemy_surfer_func, const std::function<void()> &disconnect_func) {
    return std::make_pair(ingredient_moved.connect(enemy_surfer_func), ingredient_stopped_moving.connect(disconnect_func));
}
