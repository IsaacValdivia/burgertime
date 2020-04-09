
#pragma once

#include "Audio.hpp"
#include "BurgerTimeController.hpp"
#include "Config.hpp"
#include "Constants.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <tinyfsm.hpp>
#include <utility>

class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine> {
protected:
    static BurgerTimeController &controller;
    static GUI &gui;

public:
    /**
     * @brief Entry state function
     *
     */
    void react(const tinyfsm::Event &) {};

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

class ConfigOptionState : public MainScreenStateMachine {
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

class InsideConfigOptionState : public MainScreenStateMachine {
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

class ResolutionScreenInsideState : public MainScreenStateMachine {
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

    /**
     * @brief Changes the resolutions text
     *
     */
    void change_resolutions_text() const;

    Config::Resolution current_resolution;
    bool is_in_exit;
};

class ResolutionScreenState : public MainScreenStateMachine {
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

class BindingsScreenInsideState : public MainScreenStateMachine {
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

    enum CurrentOption {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION,
        EXIT,
        BACK,
        NUM_OPTIONS,
    };

    static constexpr std::array<const char *, 13> OPTION_STRINGS = {
        "bindingsScreenUp", "bindingsScreenUpKey", "bindingsScreenDown",
        "bindingsScreenDownKey", "bindingsScreenLeft", "bindingsScreenLeftKey",
        "bindingsScreenRight", "bindingsScreenRightKey", "bindingsScreenAction",
        "bindingsScreenActionKey", "bindingsScreenExit", "bindingsScreenExitKey",
        "bindingsScreenBack"
    };

    CurrentOption current_option;
    bool is_reading_key;
    sf::Keyboard::Key last_read_key;
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

class ResolutionOptionState : public MainScreenStateMachine {
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

class BackOptionState : public MainScreenStateMachine {
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
