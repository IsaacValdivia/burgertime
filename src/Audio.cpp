#include "Audio.hpp"

#include <iostream>

#include <SFML/Audio.hpp>

namespace Audio {
    namespace {
        static constexpr size_t NUM_AUDIO_FILES = 17;

        // static sf::SoundBuffer sound_buffer;

        struct Sounds {
            sf::SoundBuffer sound_buffer;
            std::string filename;
            sf::Sound sound;
            bool loop;
        };

        static Sounds sounds[] = {
            {.filename = "audio/0_burger_going_down.ogg", .loop = false},
            {.filename = "audio/1_burger_touching_floor.ogg", .loop = false},
            {.filename = "audio/2_die.ogg", .loop = false},
            {.filename = "audio/3_high_scores.ogg", .loop = false},
            {.filename = "audio/4_entry_selected.ogg", .loop = false},
            {.filename = "audio/5_coin_inserted.ogg", .loop = false},
            {.filename = "audio/6_one_up.ogg", .loop = false},
            {.filename = "audio/7_enemy_crushed.ogg", .loop = false},
            {.filename = "audio/8_enemy_fall.ogg", .loop = false},
            {.filename = "audio/9_getting_points.ogg", .loop = false},
            {.filename = "audio/10_level_intro.ogg", .loop = false},
            {.filename = "audio/11_main.ogg", .loop = true},
            {.filename = "audio/12_main_bip.ogg", .loop = true},
            {.filename = "audio/13_new_ingredient.ogg", .loop = false},
            {.filename = "audio/14_pepper.ogg", .loop = false},
            {.filename = "audio/15_peppered.ogg", .loop = false},
            {.filename = "audio/16_stepping_on_burger.ogg", .loop = false},
            {.filename = "audio/17_win.ogg", .loop = false}
        };
    }

    void init() {
        for (size_t i = 0; i < NUM_AUDIO_FILES; ++i) {
            if (!sounds[i].sound_buffer.loadFromFile(sounds[i].filename)) {
                fprintf(stderr, "Error while loading audio files\n");
            }
            else {
                sounds[i].sound.setBuffer(sounds[i].sound_buffer);

                if (sounds[i].loop) {
                    sounds[i].sound.setLoop(true);
                }
            }
        }
    }

    void play(Track track) {
        sounds[track].sound.play();
    }

    void stop(Track track) {
        sounds[track].sound.stop();
    }
}