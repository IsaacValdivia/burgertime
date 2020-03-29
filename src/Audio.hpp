#pragma once

namespace Audio {
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
    void init();

    void play(Track track);
    void stop(Track track);
    void stopBackground();
}

