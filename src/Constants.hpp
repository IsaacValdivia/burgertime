#pragma once

#include <tinyfsm.hpp>

// How many times per second the logic will be updated
static constexpr float LOGIC_UPDATE_FREQ = 1.0 / 100;

static constexpr auto WINDOW_WIDTH = 550; // Width of the window
static constexpr auto WINDOW_HEIGHT = 550; // Height of the window
static constexpr auto ASPECT_RATIO = WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT);
static constexpr auto WINDOW_TITLE = "Burger Time!";
static constexpr auto FONT_FILE = "resources/PressStart2P-vaV7.ttf";
static constexpr auto HSCORE_FILE = "resources/btime.hscores";
static constexpr auto SPRITES_FILE = "img/burger_time_characters_and_objects_sprites.png";
static constexpr auto MAPS_FOLDER = "maps";
static constexpr auto MAP_EXTENSION = ".map";
static constexpr auto INGMAP_EXTENSION = ".ingmap";
static constexpr auto MAX_SCORE_CHARS = 6;

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NUM_DIRECTIONS
};

struct ExecuteEvent : tinyfsm::Event {
    ExecuteEvent() = delete;
    ExecuteEvent(float delta_t) : delta_t(delta_t) {}

    const float delta_t;
};
