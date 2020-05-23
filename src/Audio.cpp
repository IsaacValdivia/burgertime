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
            {.filename = "audio/4_entry_selected.ogg", .loop = false},
            {.filename = "audio/5_coin_inserted.ogg", .loop = false},
            {.filename = "audio/6_one_up.ogg", .loop = false},
            {.filename = "audio/7_enemy_crushed.ogg", .loop = false},
            {.filename = "audio/8_enemy_fall.ogg", .loop = false},
            {.filename = "audio/9_pepper_up.ogg", .loop = false},
            {.filename = "audio/13_new_ingredient.ogg", .loop = false},
            {.filename = "audio/14_pepper.ogg", .loop = false},
            {.filename = "audio/15_peppered.ogg", .loop = false},
            {.filename = "audio/16_stepping_on_burger.ogg", .loop = false},
            {.filename = "audio/18_menu_select.ogg", .loop = false},
            {.filename = "audio/20_menu_move.ogg", .loop = false}
        };

        static Sounds musics[] = {
            {.filename = "audio/2_die.ogg", .loop = false},
            {.filename = "audio/3_high_scores.ogg", .loop = false},
            {.filename = "audio/10_level_intro.ogg", .loop = false},
            {.filename = "audio/11_main.ogg", .loop = true},
            {.filename = "audio/12_main_bip.ogg", .loop = true},
            {.filename = "audio/17_win.ogg", .loop = false},
            {.filename = "audio/19_burgermenu.ogg", .loop = true},
        };

        static constexpr size_t NUM_SFX_FILES = sizeof(sounds) / sizeof(sounds[0]);
        static constexpr size_t NUM_MUSIC_FILES = sizeof(musics) / sizeof(musics[0]);

        static std::array<bool, NUM_SFX_FILES> was_sfx_playing;
        static std::array<bool, NUM_MUSIC_FILES> was_music_playing;
    }

    void init() {
        // Initialise music assets
        for (size_t i = 0; i < NUM_MUSIC_FILES; ++i) {
            if (!musics[i].sound_buffer.loadFromFile(musics[i].filename)) {
                throw std::runtime_error("Error while loading music files");
            }
            else {
                musics[i].sound.setBuffer(musics[i].sound_buffer);

                if (musics[i].loop) {
                    musics[i].sound.setLoop(true);
                }
            }
        }

        // Initialise SFX assets
        for (size_t i = 0; i < NUM_SFX_FILES; ++i) {
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

    void pause_all_sfx() {
        for (size_t i = 0; i < NUM_SFX_FILES; i++) {
            was_sfx_playing[i] = false;

            if (sounds[i].sound.getStatus() == sf::SoundSource::Playing) {
                was_sfx_playing[i] = true;
                sounds[i].sound.pause();
            }
        }
    }

    void pause_all_music() {
        for (size_t i = 0; i < NUM_MUSIC_FILES; i++) {
            was_music_playing[i] = false;

            if (musics[i].sound.getStatus() == sf::SoundSource::Playing) {
                was_music_playing[i] = true;
                musics[i].sound.pause();
            }
        }
    }

    void pause_all() {
        pause_all_sfx();
        pause_all_music();
    }

    void resume_all_sfx() {
        for (size_t i = 0; i < NUM_SFX_FILES; i++) {
            if (was_sfx_playing[i]) {
                sounds[i].sound.play();
            }
        }
    }

    void resume_all_music() {
        for (size_t i = 0; i < NUM_MUSIC_FILES; i++) {
            if (was_music_playing[i]) {
                musics[i].sound.play();
            }
        }
    }

    void resume_all() {
        resume_all_sfx();
        resume_all_music();
    }

    void set_sfx_vol(const unsigned int vol) {
        for (size_t i = 0; i < NUM_SFX_FILES; i++) {
            sounds[i].sound.setVolume(vol);
        }
    }

    void set_music_vol(const unsigned int vol) {
        for (size_t i = 0; i < NUM_MUSIC_FILES; i++) {
            musics[i].sound.setVolume(vol);
        }
    }

    void play(const Track track) {
        sounds[track].sound.play();
    }

    void play(const MusicTrack track) {
        musics[track].sound.play();
    }

    void stop(const Track track) {
        sounds[track].sound.stop();
    }

    void stop(const MusicTrack track) {
        musics[track].sound.stop();
    }

    void stop_background() {
        musics[MAIN].sound.stop();
        sounds[LEVEL_INTRO].sound.stop();
        musics[MAIN_BIP].sound.stop();
    }

    bool is_playing(const Track track) {
        return sounds[track].sound.getStatus() == sf::SoundSource::Playing;
    }

    bool is_playing(const MusicTrack track) {
        return musics[track].sound.getStatus() == sf::SoundSource::Playing;
    }
}
