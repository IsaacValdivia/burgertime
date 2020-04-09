#pragma once

namespace Audio {
    // Enumeration of different soundtracks in the game
    enum Track {
        BURGER_GOING_DOWN,
        BURGER_TOUCHING_FLOOR,
        DIE,
        HIGH_SCORES,
        ENTRY_SELECTED,
        COIN_INSERTED,
        ONE_UP,
        ENEMY_CRUSHED,
        ENEMY_FALL,
        PEPPER_UP,
        LEVEL_INTRO,
        MAIN,
        MAIN_BIP,
        NEW_INGREDIENT,
        PEPPER,
        PEPPERED,
        STEPPING_ON_BURGER,
        WIN
    };

    /**
     * @brief Initialises sound and music structures
     *
     */
    void init();

    /**
     * @brief Starts the reproduction of a selected track
     *
     * @param track track to play
     */
    void play(const Track track);

    /**
     * @brief Stops the reproduction of a selected track
     *
     * @param track track to stop
     */
    void stop(const Track track);

    /**
     * @brief Stops the reproduction of main level music and level intro
     *
     */
    void stop_background();

    /**
     * @brief Checks whether a certain track is being played at the moment
     *
     * @param track track to check
     * @return true
     * @return false
     */
    bool is_playing(const Track track);
}

