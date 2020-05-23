#pragma once

namespace Audio {
    // Enumeration of different soundtracks in the game
    enum Track {
        BURGER_GOING_DOWN,
        BURGER_TOUCHING_FLOOR,
        ENTRY_SELECTED,
        COIN_INSERTED,
        ONE_UP,
        ENEMY_CRUSHED,
        ENEMY_FALL,
        PEPPER_UP,
        NEW_INGREDIENT,
        PEPPER,
        PEPPERED,
        STEPPING_ON_BURGER,
        MENU_SELECT,
        MENU_MOVE
    };

    enum MusicTrack {
        DIE,
        HIGH_SCORES,
        LEVEL_INTRO,
        MAIN,
        MAIN_BIP,
        WIN,
        MENU_MUSIC,
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

    void play(const MusicTrack track);

    /**
     * @brief Stops the reproduction of a selected track
     *
     * @param track track to stop
     */
    void stop(const Track track);

    void stop(const MusicTrack track);

    void set_sfx_vol(const unsigned int vol);

    void set_music_vol(const unsigned int vol);

    void pause_all_sfx();

    void pause_all_music();

    /**
     * Pause every sound playing right now.
     * 
     */
    void pause_all();

    void resume_all_sfx();

    void resume_all_music();

    /**
     * Resume every sound that was playing before calling pause_all().
     * 
     */
    void resume_all();

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

    bool is_playing(const MusicTrack track);
}

