#pragma once

#include "Audio.hpp"
#include "BurgerTimeController.hpp"
#include "Constants.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include "BurgerTimeController.hpp"
#include "Config.hpp"
#include "Audio.hpp"

class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine> {
public:
    void react(const tinyfsm::Event &) {};

    class MainScreenStateMachine : public tinyfsm::MooreMachine<MainScreenStateMachine> {
    protected:
        static constexpr auto START_SELECTION_POSITION = std::make_pair(
                    32 * WINDOW_WIDTH / 100 - 13, 3 * WINDOW_HEIGHT / 10);

        static constexpr auto BINDINGS_SELECTION_POSITION = std::make_pair(
                    32 * WINDOW_WIDTH / 100 - 13, 4 * WINDOW_HEIGHT / 10);

    protected:
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

    class ConfigOptionState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;
    };

    class InsideConfigOptionState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;
    };

    class ResolutionScreenInsideState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;

        void changeResolutionsText() const;

        Config::Resolution current_resolution;
        bool isInExit;
    };

    class ResolutionScreenState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;
    };

    class BindingsScreenInsideState : public MainScreenStateMachine {
        void entry() override;
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
            "bindingsScreenUp", "bindingsScreenUpKey", "bindingsScreenDown", "bindingsScreenDownKey",
            "bindingsScreenLeft", "bindingsScreenLeftKey", "bindingsScreenRight", "bindingsScreenRightKey",
            "bindingsScreenAction", "bindingsScreenActionKey", "bindingsScreenExit", "bindingsScreenExitKey",
            "bindingsScreenBack"
        };

        CurrentOption currentOption;
        bool isReadingKey;
        sf::Keyboard::Key lastReadKey;
    };

    class BindingsOptionState : public MainScreenStateMachine {
        void entry() override;

        /**
         * @brief Main control function
         *
         */
        void react(const ExecuteEvent &) override;
    };

    class ResolutionOptionState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;
    };

    class BackOptionState : public MainScreenStateMachine {
        void entry() override;
        void react(const ExecuteEvent &) override;
    };

    class ExitOptionState : public MainScreenStateMachine {
        void entry() override;

        /**
         * @brief Main control function
         *
         */
        void react(const ExecuteEvent &) override;
    };

    class FinishedStartState : public MainScreenStateMachine {};

    class FinishedExitState : public MainScreenStateMachine {};
}
