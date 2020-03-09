#include "BT_sprites.hpp"

const int BT_sprites::containers[][DIMENSIONS] = {
    /*
    * Regular size sprites.
    */

    // Regular size sprites line 0
    {sprite_size * 0, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_DOWNSTAIRS_1
    {sprite_size * 1, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_STILL_FRONT
    {sprite_size * 2, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_DOWNSTAIRS_2
    {sprite_size * 3, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_LEFT_1
    {sprite_size * 4, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_LEFT_2
    {sprite_size * 5, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_LEFT_3
    {sprite_size * 6, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_UPSTAIRS_1
    {sprite_size * 7, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_STILL_BACK
    {sprite_size * 8, sprite_size * 0, sprite_size, sprite_size}, // PLAYER_UPSTAIRS_2
    // Regular size sprites line 1
    {sprite_size * 0, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_PEPPER_FRONT
    {sprite_size * 1, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_PEPPER_LEFT
    {sprite_size * 2, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_PEPPER_BACK
    {sprite_size * 3, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_CELEBRATING
    {sprite_size * 4, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_DROP_1
    {sprite_size * 5, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_DROP_2
    {sprite_size * 6, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_DROP_3
    {sprite_size * 7, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_DROP_4
    {sprite_size * 8, sprite_size * 1, sprite_size, sprite_size}, // PLAYER_DROP_5
    // Regular size sprites line 2
    {sprite_size * 0, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_DOWNSTAIRS_1
    {sprite_size * 1, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_DOWNSTAIRS_2
    {sprite_size * 2, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_LEFT_1
    {sprite_size * 3, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_LEFT_2
    {sprite_size * 4, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_UPSTAIRS_2
    {sprite_size * 5, sprite_size * 2, sprite_size, sprite_size}, // SAUSAGE_UPSTAIRS_2
    // Regular size sprites line 3
    {sprite_size * 0, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_CRUSHED_1
    {sprite_size * 1, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_CRUSHED_2
    {sprite_size * 2, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_CRUSHED_3
    {sprite_size * 3, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_CRUSHED_4
    {sprite_size * 4, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_PEPPER_2
    {sprite_size * 5, sprite_size * 3, sprite_size, sprite_size}, // SAUSAGE_PEPPER_1
    // Regular size sprites line 4
    {sprite_size * 0, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_DOWNSTAIRS_1
    {sprite_size * 1, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_DOWNSTAIRS_2
    {sprite_size * 2, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_LEFT_1
    {sprite_size * 3, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_LEFT_2
    {sprite_size * 4, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_UPSTAIRS_2
    {sprite_size * 5, sprite_size * 4, sprite_size, sprite_size}, // PICKLE_UPSTAIRS_2
    // Regular size sprites line 5
    {sprite_size * 0, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_CRUSHED_1
    {sprite_size * 1, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_CRUSHED_2
    {sprite_size * 2, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_CRUSHED_3
    {sprite_size * 3, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_CRUSHED_4
    {sprite_size * 4, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_PEPPER_2
    {sprite_size * 5, sprite_size * 5, sprite_size, sprite_size}, // PICKLE_PEPPER_1
    // Regular size sprites line 6
    {sprite_size * 0, sprite_size * 6, sprite_size, sprite_size}, // EGG_DOWNSTAIRS_1
    {sprite_size * 1, sprite_size * 6, sprite_size, sprite_size}, // EGG_DOWNSTAIRS_2
    {sprite_size * 2, sprite_size * 6, sprite_size, sprite_size}, // EGG_LEFT_1
    {sprite_size * 3, sprite_size * 6, sprite_size, sprite_size}, // EGG_LEFT_2
    {sprite_size * 4, sprite_size * 6, sprite_size, sprite_size}, // EGG_UPSTAIRS_2
    {sprite_size * 5, sprite_size * 6, sprite_size, sprite_size}, // EGG_UPSTAIRS_2
    // Regular size sprites line 7
    {sprite_size * 0, sprite_size * 7, sprite_size, sprite_size}, // EGG_CRUSHED_1
    {sprite_size * 1, sprite_size * 7, sprite_size, sprite_size}, // EGG_CRUSHED_2
    {sprite_size * 2, sprite_size * 7, sprite_size, sprite_size}, // EGG_CRUSHED_3
    {sprite_size * 3, sprite_size * 7, sprite_size, sprite_size}, // EGG_CRUSHED_4
    {sprite_size * 4, sprite_size * 7, sprite_size, sprite_size}, // EGG_PEPPER_2
    {sprite_size * 5, sprite_size * 7, sprite_size, sprite_size}, // EGG_PEPPER_1
    // Regular size sprites line 8
    {sprite_size * 0, sprite_size * 8, sprite_size, sprite_size}, // ICE_CREAM
    {sprite_size * 1, sprite_size * 8, sprite_size, sprite_size}, // COFFEE
    {sprite_size * 2, sprite_size * 8, sprite_size, sprite_size}, // FRIES
    // Regular size sprites line 9
    {sprite_size * 0, sprite_size * 9, sprite_size, sprite_size}, // P_300
    {sprite_size * 1, sprite_size * 9, sprite_size, sprite_size}, // P_600
    {sprite_size * 2, sprite_size * 9, sprite_size, sprite_size}, // P_900
    {sprite_size * 3, sprite_size * 9, sprite_size, sprite_size}, // P_500
    {sprite_size * 4, sprite_size * 9, sprite_size, sprite_size}, // P_1000
    {sprite_size * 5, sprite_size * 9, sprite_size, sprite_size}, // P_1500
    // Regular size sprites line 10
    {sprite_size * 0, sprite_size * 10, sprite_size, sprite_size}, // P_100
    {sprite_size * 1, sprite_size * 10, sprite_size, sprite_size}, // P_200
    {sprite_size * 2, sprite_size * 10, sprite_size, sprite_size}, // // P_300
    {sprite_size * 3, sprite_size * 10, sprite_size, sprite_size}, // // P_500
    {sprite_size * 4, sprite_size * 10, sprite_size, sprite_size}, // // P_1000
    {sprite_size * 5, sprite_size * 10, sprite_size, sprite_size}, // P_2000
    {sprite_size * 6, sprite_size * 10, sprite_size, sprite_size}, // P_4000
    {sprite_size * 7, sprite_size * 10, sprite_size, sprite_size}, // P_8000
    {sprite_size * 8, sprite_size * 10, sprite_size, sprite_size}, // P_16000

    /*
     * Burger sprites.
     */

    // Burger sprites line 0
    {small_sprite_size * 14, small_sprite_size * 6, small_sprite_size, small_sprite_size}, // TOP_BREAD_1
    {small_sprite_size * 15, small_sprite_size * 6, small_sprite_size, small_sprite_size}, // TOP_BREAD_2
    {small_sprite_size * 16, small_sprite_size * 6, small_sprite_size, small_sprite_size}, // TOP_BREAD_3
    {small_sprite_size * 17, small_sprite_size * 6, small_sprite_size, small_sprite_size}, // TOP_BREAD_4
    // Burger sprites line 1
    {small_sprite_size * 14, small_sprite_size * 7, small_sprite_size, small_sprite_size}, // BOTTOM_BREAD_1
    {small_sprite_size * 15, small_sprite_size * 7, small_sprite_size, small_sprite_size}, // BOTTOM_BREAD_2
    {small_sprite_size * 16, small_sprite_size * 7, small_sprite_size, small_sprite_size}, // BOTTOM_BREAD_3
    {small_sprite_size * 17, small_sprite_size * 7, small_sprite_size, small_sprite_size}, // BOTTOM_BREAD_4
    // Burger sprites line 2
    {small_sprite_size * 14, small_sprite_size * 8, small_sprite_size, small_sprite_size}, // CHEESE_1
    {small_sprite_size * 15, small_sprite_size * 8, small_sprite_size, small_sprite_size}, // CHEESE_2
    {small_sprite_size * 16, small_sprite_size * 8, small_sprite_size, small_sprite_size}, // CHEESE_3
    {small_sprite_size * 17, small_sprite_size * 8, small_sprite_size, small_sprite_size}, // CHEESE_4
    // Burger sprites line 3
    {small_sprite_size * 14, small_sprite_size * 9, small_sprite_size, small_sprite_size}, // BURGER_1
    {small_sprite_size * 15, small_sprite_size * 9, small_sprite_size, small_sprite_size}, // BURGER_2
    {small_sprite_size * 16, small_sprite_size * 9, small_sprite_size, small_sprite_size}, // BURGER_3
    {small_sprite_size * 17, small_sprite_size * 9, small_sprite_size, small_sprite_size}, // BURGER_4
    // Burger sprites line 4
    {small_sprite_size * 14, small_sprite_size * 10, small_sprite_size, small_sprite_size}, // TOMATO_1
    {small_sprite_size * 15, small_sprite_size * 10, small_sprite_size, small_sprite_size}, // TOMATO_2
    {small_sprite_size * 16, small_sprite_size * 10, small_sprite_size, small_sprite_size}, // TOMATO_3
    {small_sprite_size * 17, small_sprite_size * 10, small_sprite_size, small_sprite_size}, // TOMATO_4
    // Burger sprites line 5
    {small_sprite_size * 14, small_sprite_size * 11, small_sprite_size, small_sprite_size}, // LETTUCE_1
    {small_sprite_size * 15, small_sprite_size * 11, small_sprite_size, small_sprite_size}, // LETTUCE_2
    {small_sprite_size * 16, small_sprite_size * 11, small_sprite_size, small_sprite_size}, // LETTUCE_3
    {small_sprite_size * 17, small_sprite_size * 11, small_sprite_size, small_sprite_size}, // LETTUCE_4

    /*
    * Indicator sprites.
    */

    // Indicator sprites line 0
    {small_sprite_size * 25, small_sprite_size * 0, small_sprite_size, small_sprite_size}, // LIVES
    {small_sprite_size * 26, small_sprite_size * 0, small_sprite_size, small_sprite_size}, // MINI_BURGER_1
    {small_sprite_size * 27, small_sprite_size * 0, small_sprite_size, small_sprite_size}, // MINI_BURGER_5
    {small_sprite_size * 28, small_sprite_size * 0, small_sprite_size, small_sprite_size}, // MINI_BURGER_10
    {small_sprite_size * 29, small_sprite_size * 0, small_sprite_size, small_sprite_size}, // WHATS_THAT
    // Indicator sprites line 1
    {small_sprite_size * 27, small_sprite_size * 1, pepper_text_sprite_size_x, small_sprite_size}, // PEPPER

    /*
    * Pepper sprites.
    */

    // Pepper sprites line 0
    {sprite_size * 11, sprite_size * 1, sprite_size, sprite_size}, // PEPPER_LEFT_1
    {sprite_size * 12, sprite_size * 1, sprite_size, sprite_size}, // PEPPER_LEFT_2
    {sprite_size * 13, sprite_size * 1, sprite_size, sprite_size}, // PEPPER_LEFT_3
    {sprite_size * 14, sprite_size * 1, sprite_size, sprite_size}, // PEPPER_LEFT_4
    // Pepper sprites line 1
    {sprite_size * 11, sprite_size * 2, sprite_size, sprite_size}, // PEPPER_FRONT_1
    {sprite_size * 12, sprite_size * 2, sprite_size, sprite_size}, // PEPPER_FRONT_2
    {sprite_size * 13, sprite_size * 2, sprite_size, sprite_size}, // PEPPER_FRONT_3
    {sprite_size * 14, sprite_size * 2, sprite_size, sprite_size}, // PEPPER_FRONT_4
    // Pepper sprites line 2
    {sprite_size * 11, sprite_size * 3, sprite_size, sprite_size}, // PEPPER_BACK_1
    {sprite_size * 12, sprite_size * 3, sprite_size, sprite_size}, // PEPPER_BACK_2
    {sprite_size * 13, sprite_size * 3, sprite_size, sprite_size}, // PEPPER_BACK_3
    {sprite_size * 14, sprite_size * 3, sprite_size, sprite_size}, // PEPPER_BACK_4
};

/**
 * Auxiliar function to init textures.
 *
 * @param path_to_sprite
 * @return sf::Texture
 */
sf::Texture create_texture(const std::string &path_to_sprite) {
    sf::Texture texture;
    texture.loadFromFile(path_to_sprite);

    return texture;
}

// Init texture.
sf::Texture BT_sprites::char_and_obj_sprites = create_texture(
            "img/burger_time_characters_and_objects_sprites.png"
        );


void BT_sprites::set_initial_sprite(sf::Sprite &sp, const Sprite new_sprite) {
    sp.setTexture(char_and_obj_sprites);
    sp.setTextureRect(sf::IntRect(
                          containers[new_sprite][padding_x_idx],
                          containers[new_sprite][padding_y_idx],
                          containers[new_sprite][x_idx],
                          containers[new_sprite][y_idx]));
};

void BT_sprites::update_sprite(sf::Sprite &sp, const Sprite new_sprite) {
    sp.setTextureRect(sf::IntRect(
                          containers[new_sprite][padding_x_idx],
                          containers[new_sprite][padding_y_idx],
                          containers[new_sprite][x_idx],
                          containers[new_sprite][y_idx]));
};

