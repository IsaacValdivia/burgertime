#pragma once

#include "Audio.hpp"
#include "BurgerTimeController.hpp"
#include "Constants.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <tinyfsm.hpp>
#include <utility>

class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine> {
protected:
    static constexpr auto START_SELECTION_POSITION = std::make_pair(
                32 * WINDOW_WIDTH / 100 - 13, 3 * WINDOW_HEIGHT / 10);

    static constexpr auto BINDINGS_SELECTION_POSITION = std::make_pair(
                32 * WINDOW_WIDTH / 100 - 13, 4 * WINDOW_HEIGHT / 10);

    static constexpr auto EXIT_SELECTION_POSITION = std::make_pair(
                32 * WINDOW_WIDTH / 100 - 13, 5 * WINDOW_HEIGHT / 10);

    static std::shared_ptr<sf::CircleShape> selection_triangle;
    static BurgerTimeController &controller;
    static GUI &gui;

public:
    /**
     * @brief Main control function
     *
     */
    void react(const tinyfsm::Event &) {};

    /**
     * @brief Main control function
     *
     */
    virtual void react(const ExecuteEvent &) {};
};


class EnterStateMainScreen : public MainScreenStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class StartOptionState : public MainScreenStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class BindingsOptionState : public MainScreenStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class ExitOptionState : public MainScreenStateMachine {
    /**
     * @brief Entry state function
     *
     */
    void entry() override;

    /**
     * @brief Main control function
     *
     */
    void react(const ExecuteEvent &) override;
};

class FinishedStartState : public MainScreenStateMachine {};

class FinishedExitState : public MainScreenStateMachine {};
