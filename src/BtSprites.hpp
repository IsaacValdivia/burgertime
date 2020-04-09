#pragma once

#include <SFML/Graphics.hpp>

namespace BtSprites {
    enum Sprite {
        /*
         * Regular size sprites.
         */

        // Regular size sprites line 0
        PLAYER_DOWNSTAIRS_1,
        PLAYER_STILL_FRONT,
        PLAYER_DOWNSTAIRS_2,
        PLAYER_LEFT_1,
        PLAYER_LEFT_2,
        PLAYER_LEFT_3,
        PLAYER_UPSTAIRS_1,
        PLAYER_STILL_BACK,
        PLAYER_UPSTAIRS_2,
        // Regular size sprites line 1
        PLAYER_PEPPER_FRONT,
        PLAYER_PEPPER_LEFT,
        PLAYER_PEPPER_BACK,
        PLAYER_CELEBRATING,
        PLAYER_DROP_1,
        PLAYER_DROP_2,
        PLAYER_DROP_3,
        PLAYER_DROP_4,
        PLAYER_DROP_5,
        // Regular size sprites line 2
        SAUSAGE_DOWNSTAIRS_1,
        SAUSAGE_DOWNSTAIRS_2,
        SAUSAGE_LEFT_1,
        SAUSAGE_LEFT_2,
        SAUSAGE_UPSTAIRS_1,
        SAUSAGE_UPSTAIRS_2,
        // Regular size sprites line 3
        SAUSAGE_CRUSHED_1,
        SAUSAGE_CRUSHED_2,
        SAUSAGE_CRUSHED_3,
        SAUSAGE_CRUSHED_4,
        SAUSAGE_PEPPER_2,
        SAUSAGE_PEPPER_1,
        // Regular size sprites line 4
        PICKLE_DOWNSTAIRS_1,
        PICKLE_DOWNSTAIRS_2,
        PICKLE_LEFT_1,
        PICKLE_LEFT_2,
        PICKLE_UPSTAIRS_1,
        PICKLE_UPSTAIRS_2,
        // Regular size sprites line 5
        PICKLE_CRUSHED_1,
        PICKLE_CRUSHED_2,
        PICKLE_CRUSHED_3,
        PICKLE_CRUSHED_4,
        PICKLE_PEPPER_2,
        PICKLE_PEPPER_1,
        // Regular size sprites line 6
        EGG_DOWNSTAIRS_1,
        EGG_DOWNSTAIRS_2,
        EGG_LEFT_1,
        EGG_LEFT_2,
        EGG_UPSTAIRS_1,
        EGG_UPSTAIRS_2,
        // Regular size sprites line 7
        EGG_CRUSHED_1,
        EGG_CRUSHED_2,
        EGG_CRUSHED_3,
        EGG_CRUSHED_4,
        EGG_PEPPER_2,
        EGG_PEPPER_1,
        // Regular size sprites line 8
        ICE_CREAM,
        COFFEE,
        FRIES,
        // Regular size sprites line 9
        P_300,
        P_600,
        P_900,
        P_500,
        P_1000,
        P_1500,
        // Regular size sprites line 10
        P_100,
        P_200,
        // P_300,
        // P_500,
        // P_1000,
        P_2000,
        P_4000,
        P_8000,
        P_16000,

        /*
         * Burger sprites.
         */

        // Burger sprites line 0
        TOP_BREAD_1,
        TOP_BREAD_2,
        TOP_BREAD_3,
        TOP_BREAD_4,
        // Burger sprites line 1
        BOTTOM_BREAD_1,
        BOTTOM_BREAD_2,
        BOTTOM_BREAD_3,
        BOTTOM_BREAD_4,
        // Burger sprites line 2
        CHEESE_1,
        CHEESE_2,
        CHEESE_3,
        CHEESE_4,
        // Burger sprites line 3
        BURGER_1,
        BURGER_2,
        BURGER_3,
        BURGER_4,
        // Burger sprites line 4
        TOMATO_1,
        TOMATO_2,
        TOMATO_3,
        TOMATO_4,
        // Burger sprites line 5
        LETTUCE_1,
        LETTUCE_2,
        LETTUCE_3,
        LETTUCE_4,

        /*
        * Indicator sprites.
        */

        // Indicator sprites line 0
        LIVES,
        MINI_BURGER_1,
        MINI_BURGER_5,
        MINI_BURGER_10,
        WHATS_THAT,
        // Indicator sprites line 1
        PEPPER,

        /*
        * Pepper sprites.
        */

        // Pepper sprites line 0
        PEPPER_LEFT_1,
        PEPPER_LEFT_2,
        PEPPER_LEFT_3,
        PEPPER_LEFT_4,
        // Pepper sprites line 1
        PEPPER_FRONT_1,
        PEPPER_FRONT_2,
        PEPPER_FRONT_3,
        PEPPER_FRONT_4,
        // Pepper sprites line 2
        PEPPER_BACK_1,
        PEPPER_BACK_2,
        PEPPER_BACK_3,
        PEPPER_BACK_4,
    };

    /**
     * @brief Set the initial sprite object
     *
     * @param sp sprite
     * @param new_sprite sprite
     */
    void set_initial_sprite(sf::Sprite &sp, const Sprite new_sprite);

    /**
     * @brief Updates the sprite to new_sprite
     *
     * @param sp sprite
     * @param new_sprite new_sprite
     */
    void update_sprite(sf::Sprite &sp, const Sprite new_sprite);

    /**
     * @brief Returns the sprite resembling the number of points points
     *
     * @param points points vinculated to sprite
     * @return Sprite
     */
    Sprite get_sprite_points(const int points);
};
