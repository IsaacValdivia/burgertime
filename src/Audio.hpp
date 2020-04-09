#pragma once

namespace Audio {
    enum Track {
        BURGER_GOING_DOWN, // DONE
        BURGER_TOUCHING_FLOOR, // DONE
        DIE, // DONE
        HIGH_SCORES, // 
        ENTRY_SELECTED, // 
        COIN_INSERTED, // DONE
        ONE_UP, // DONE
        ENEMY_CRUSHED, // DONE
        ENEMY_FALL, // DONE
        PEPPER_UP, // DONE
        LEVEL_INTRO, // DONE
        MAIN, // DONE, ARREGLAR TIEMPO
        MAIN_BIP, // UNUSED
        NEW_INGREDIENT, // DONE
        PEPPER, // DONE
        PEPPERED, // DONE
        STEPPING_ON_BURGER, // DONE
        WIN // DONE
    };
    void init();

    bool is_playing(Track track);
    void play(Track track);
    void stop(Track track);
    void stopBackground();
}

