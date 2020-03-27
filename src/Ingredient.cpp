#include "Ingredient.hpp"

Ingredient::Ingredient(const float _x, const float _y, const uint8_t _row, const uint8_t _col, const char _content) : falling(false), col(_col), row(_row), content(_content) {
	std::array<BT_sprites::Sprite, ING_LENGTH> sprite_indicators;

	switch (_content)
	{
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
		pieces[i] = std::make_shared<IngredientPiece>(sf::Vector2f(_x + offset_x + (i * 16), _y + offset_y), sprite_indicators[i], row, col + i);
	}
};

void Ingredient::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (auto& piece : pieces) {
		target.draw(*piece, states);
	}
}

void Ingredient::update(float delta_t) {
	if (falling) {
		for (auto piece : pieces) {
			piece->update(delta_t);
		}
	} else {
		// COUNT NUMBER OF STEPS
		unsigned int step_num = 0;
		for (auto &piece : pieces) {
			if (piece->stepped) {
				++step_num;
			}
		}
		// FALLING TO TRUE IF 4
		if (step_num >= 4) {
			drop();
		}
	}
}

void Ingredient::drop() {
	falling = true;
	for (auto piece : pieces) {
		piece->drop();
	}
}

void Ingredient::land() {
	falling = false;
	for (auto piece : pieces) {
		piece->land();
	}
}

void Ingredient::stepped(const sf::FloatRect &rectangle) const {
	for (int i = 0; i < ING_LENGTH; ++i) {
		if (pieces[i]->getCollisionShape().intersects(rectangle) && !pieces[i]->isStepped()) {
			pieces[i]->step();
			pieces[i]->move();
			
			// LEFT
			for (int j = i - 1; j >= 0; --j) {
				if (pieces[j]->isStepped()) {
					pieces[j]->move();
				}
				else {
					break;
				}
			}

			for (int k = i + 1; k < ING_LENGTH; k++) {
				if (pieces[k]->isStepped()) {
					pieces[k]->move();
				}
				else {
					break;
				}
			}

			return;
		}
	}
}
