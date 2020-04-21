#include "Audio.hpp"

#include <exception>
#include <iostream>
#include <SFML/Audio.hpp>

namespace Audio {
    namespace {
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
            {.filename = "audio/9_pepper_up.ogg", .loop = false},
            {.filename = "audio/10_level_intro.ogg", .loop = false},
            {.filename = "audio/11_main.ogg", .loop = true},
            {.filename = "audio/12_main_bip.ogg", .loop = true},
            {.filename = "audio/13_new_ingredient.ogg", .loop = false},
            {.filename = "audio/14_pepper.ogg", .loop = false},
            {.filename = "audio/15_peppered.ogg", .loop = false},
            {.filename = "audio/16_stepping_on_burger.ogg", .loop = false},
            {.filename = "audio/17_win.ogg", .loop = false}
        };

        static constexpr size_t NUM_AUDIO_FILES = sizeof(sounds) / sizeof(sounds[0]);

        static std::array<bool, NUM_AUDIO_FILES> was_playing;
    }

    void init() {
        for (size_t i = 0; i < NUM_AUDIO_FILES; ++i) {
            if (!sounds[i].sound_buffer.loadFromFile(sounds[i].filename)) {
                throw std::runtime_error("Error while loading audio files");
            }
            else {
                sounds[i].sound.setBuffer(sounds[i].sound_buffer);

                if (sounds[i].loop) {
                    sounds[i].sound.setLoop(true);
                }
            }
        }
    }

    void pause_all() {
        for (size_t i = 0; i < NUM_AUDIO_FILES; i++) {
            was_playing[i] = false;

            if (sounds[i].sound.getStatus() == sf::SoundSource::Playing) {
                was_playing[i] = true;
                sounds[i].sound.pause();
            }
        }
    }

    void resume_all() {
        for (size_t i = 0; i < NUM_AUDIO_FILES; i++) {
            if (was_playing[i]) {
                sounds[i].sound.play();
            }
        }
    }

    void play(const Track track) {
        sounds[track].sound.play();
    }

    void stop(const Track track) {
        sounds[track].sound.stop();
    }

    void stop_background() {
        sounds[MAIN].sound.stop();
        sounds[LEVEL_INTRO].sound.stop();
        sounds[MAIN_BIP].sound.stop();
    }

    bool is_playing(const Track track) {
        return sounds[track].sound.getStatus() == sf::SoundSource::Playing;
    }
}
