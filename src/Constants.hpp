#pragma once

#include <tinyfsm.hpp>

// How many times per second the logic will be updated
static constexpr float LOGIC_UPDATE_FREQ = 1.0 / 100;

static constexpr auto WINDOW_WIDTH = 550;
static constexpr auto WINDOW_HEIGHT = 550;
static constexpr auto ASPECT_RATIO = WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT);
static constexpr auto WINDOW_TITLE = "Burger Time!";
static constexpr auto FONT_FILE = "resources/PressStart2P-vaV7.ttf";
static constexpr auto SPRITES_FILE = "img/burger_time_characters_and_objects_sprites.png";

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NUM_DIRECTIONS
};

struct ExecuteEvent : tinyfsm::Event 
{
    ExecuteEvent() = delete;
    ExecuteEvent(float deltaT) : deltaT(deltaT) {}
    
    const float deltaT;
};
