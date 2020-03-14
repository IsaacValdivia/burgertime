#pragma once

#include <tinyfsm.hpp>

// How many times per second the logic will be updated
static constexpr float LOGIC_UPDATE_FREQ = 1.0 / 100;

static constexpr auto WINDOW_WIDTH = 486;
static constexpr auto WINDOW_HEIGHT = 486;
static constexpr auto ASPECT_RATIO = WINDOW_WIDTH / static_cast<float>(WINDOW_HEIGHT);
static constexpr auto WINDOW_TITLE = "Burger Time!";
static constexpr auto FONT_FILE = "resources/PressStart2P-vaV7.ttf";

struct ExecuteEvent : tinyfsm::Event {};
