#include "Ingredient.hpp"

#include "Audio.hpp"

Ingredient::IngredientPiece::IngredientPiece(const sf::Vector2f &_init_pos,
        BtSprites::Sprite _init_sprite) :

    SpritedEntity(_init_pos, _init_sprite), stepped(false) {
    this->sprite.setScale(2, 2);
}

void Ingredient::IngredientPiece::step() {
    stepped = true;
    this->sprite.move(0, y_movement_static);
}

bool Ingredient::IngredientPiece::is_stepped() const {
    return stepped;
}

void Ingredient::IngredientPiece::move_y(float magnitude) {
    this->sprite.move(0, magnitude);
}

sf::FloatRect Ingredient::IngredientPiece::get_collision_shape() const {
    sf::FloatRect collision_shape = sprite.getGlobalBounds();

    collision_shape.left += 10;
    collision_shape.width -= 20;

    return collision_shape;
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
    float lowest_y = 0;

    for (auto &piece : pieces) {
        float y = piece.sprite.getPosition().y;
        if (y > lowest_y) {
            lowest_y = y;
        }
    }

    for (auto &piece : pieces) {
        auto position = piece.sprite.getPosition();
        piece.sprite.setPosition(position.x, lowest_y);
    }
}

void Ingredient::fix_position_up() {
    float highest_y = pieces[0].sprite.getPosition().y;

    for (auto &piece : pieces) {
        float y = piece.sprite.getPosition().y;
        if (y < highest_y) {
            highest_y = y;
        }
    }

    for (auto &piece : pieces) {
        auto position = piece.sprite.getPosition();
        piece.sprite.setPosition(position.x, highest_y);
    }
}

void Ingredient::fix_to_y(const float y) {
    for (auto &piece : pieces) {
        piece.sprite.setPosition(piece.sprite.getPosition().x, y);
    }
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
void Ingredient::reset_steps() {
    for (auto &piece : pieces) {
        piece.stepped = false;
    }
}

Ingredient::Ingredient(const float _x, const float _y, const Type _content) :
    state(IDLE), content(_content), last_landable(NONE), num_levels(1),
    static_tested(false) {

    std::array<BtSprites::Sprite, ING_LENGTH> sprite_indicators;

    switch (_content) {
        case TOP_BUN:
            sprite_indicators[0] = BtSprites::Sprite::TOP_BREAD_1;
            sprite_indicators[1] = BtSprites::Sprite::TOP_BREAD_2;
            sprite_indicators[2] = BtSprites::Sprite::TOP_BREAD_3;
            sprite_indicators[3] = BtSprites::Sprite::TOP_BREAD_4;
            break;

        case BOT_BUN:
            sprite_indicators[0] = BtSprites::Sprite::BOTTOM_BREAD_1;
            sprite_indicators[1] = BtSprites::Sprite::BOTTOM_BREAD_2;
            sprite_indicators[2] = BtSprites::Sprite::BOTTOM_BREAD_3;
            sprite_indicators[3] = BtSprites::Sprite::BOTTOM_BREAD_4;
            break;

        case MEAT:
            sprite_indicators[0] = BtSprites::Sprite::BURGER_1;
            sprite_indicators[1] = BtSprites::Sprite::BURGER_2;
            sprite_indicators[2] = BtSprites::Sprite::BURGER_3;
            sprite_indicators[3] = BtSprites::Sprite::BURGER_4;
            break;

        case CHEESE:
            sprite_indicators[0] = BtSprites::Sprite::CHEESE_1;
            sprite_indicators[1] = BtSprites::Sprite::CHEESE_2;
            sprite_indicators[2] = BtSprites::Sprite::CHEESE_3;
            sprite_indicators[3] = BtSprites::Sprite::CHEESE_4;
            break;

        case LETTUCE:
            sprite_indicators[0] = BtSprites::Sprite::LETTUCE_1;
            sprite_indicators[1] = BtSprites::Sprite::LETTUCE_2;
            sprite_indicators[2] = BtSprites::Sprite::LETTUCE_3;
            sprite_indicators[3] = BtSprites::Sprite::LETTUCE_4;
            break;

        case TOMATO:
            sprite_indicators[0] = BtSprites::Sprite::TOMATO_1;
            sprite_indicators[1] = BtSprites::Sprite::TOMATO_2;
            sprite_indicators[2] = BtSprites::Sprite::TOMATO_3;
            sprite_indicators[3] = BtSprites::Sprite::TOMATO_4;
            break;

        default:
            break;
    }

    const float offset_x = 16 / 2.0;
    const float offset_y = 16 / 2.0;
    for (unsigned int i = 0; i < ING_LENGTH; ++i) {
        pieces.emplace_back(sf::Vector2f(_x + offset_x + (i * 16), _y + offset_y),
                            sprite_indicators[i]);
    }
}

Ingredient::Ingredient(Ingredient &&other) noexcept :
    state(other.state), content(other.content), last_landable(other.last_landable),
    num_levels(other.num_levels), static_tested(other.static_tested),
    ingredient_moved(std::move(other.ingredient_moved)), ingredient_stopped_moving(
        std::move(other.ingredient_stopped_moving)), pieces(std::move(other.pieces)) {}

void Ingredient::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &piece : pieces) {
        target.draw(piece, states);
    }

#if false
    auto collision_shape = get_collision_shape();
    sf::RectangleShape drawShape;
    drawShape.setOutlineColor(sf::Color::Red);
    drawShape.setFillColor(sf::Color::Transparent);
    drawShape.setOutlineThickness(1);
    drawShape.setPosition(collision_shape.left, collision_shape.top);
    drawShape.setSize(sf::Vector2f(collision_shape.width, collision_shape.height));
    target.draw(drawShape, states);
#endif
}

void Ingredient::update(const float delta_t) {
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

bool Ingredient::stepped(const sf::FloatRect &rectangle, const int _num_levels) {
    if (state == IDLE) {

        int stepped_count = 0;

        for (int i = 0; i < ING_LENGTH; ++i) {
            if (pieces[i].get_collision_shape().intersects(rectangle) && !pieces[i].is_stepped()) {
                pieces[i].step();

                Audio::play(Audio::Track::STEPPING_ON_BURGER);

                // LEFT
                for (int j = i - 1; j >= 0; --j) {
                    if (pieces[j].is_stepped()) {
                        pieces[j].step();
                    }
                    else {
                        break;
                    }
                }

                // RIGHT
                for (int k = i + 1; k < ING_LENGTH; k++) {
                    if (pieces[k].is_stepped()) {
                        pieces[k].step();
                    }
                    else {
                        break;
                    }
                }
            }

            if (pieces[i].is_stepped()) {
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

sf::FloatRect Ingredient::get_collision_shape() const {
    sf::FloatRect collision_shape = pieces[0].sprite.getGlobalBounds();
    collision_shape.width *= 4;

    // collision_shape.height -= 13;

    // for (const auto &piece : pieces)
    // {
    //     if (piece.sprite.getGlobalBounds().top > collision_shape.top)
    //     {
    //         collision_shape.top = piece.sprite.getGlobalBounds().top;
    //     }
    // }

    return collision_shape;
}

void Ingredient::drop() {
    fix_position_down();

    move_down_no_delta(1);
    reset_steps();
    state = FALLING;
}

void Ingredient::land(const float y, const Landable landable) {
    if (pieces[0].sprite.getPosition().y >= y - 6) {
        fix_to_y(y);

        if (landable == last_landable) {
            descend_and_check();

            return;
        }

        Audio::play(Audio::Track::BURGER_TOUCHING_FLOOR);

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

void Ingredient::reset() {
    reset_steps();
    fix_position_up();
}

bool Ingredient::test_static() {
    if (state == STATIC && !static_tested) {
        static_tested = true;

        return true;
    }
    return false;
}

bool Ingredient::is_static() const {
    return state == STATIC;
}

bool Ingredient::is_idle() const {
    return state == IDLE;
}

bool Ingredient::is_falling() const {
    return state == FALLING;
}

bool Ingredient::is_bouncing() const {
    return state == BOUNCE_UP_1 ||
           state == BOUNCE_UP_2 ||
           state == BOUNCE_UP_3 ||
           state == BOUNCE_DOWN_1 ||
           state == BOUNCE_DOWN_2 ||
           state == BOUNCE_DOWN_3;
}

std::pair<nod::connection, nod::connection> Ingredient::connect_enemy_surfer(
    const std::function<void(float)> &enemy_surfer_func,
    const std::function<void()> &disconnect_func) {

    return std::make_pair(ingredient_moved.connect(enemy_surfer_func),
                          ingredient_stopped_moving.connect(disconnect_func));
}
