#include "BurgerTimeStateMachine.hpp"

#include "BtSprites.hpp"
#include "InputSystem.hpp"
#include "MainScreenStateMachine.hpp"
#include "PlayingStateMachine.hpp"

// #include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

FSM_INITIAL_STATE(BurgerTimeStateMachine, HighscoreDisplayScreenState)

BurgerTimeController &BurgerTimeStateMachine::controller = BurgerTimeController::get();
GUI &BurgerTimeStateMachine::gui = GUI::get();


bool BurgerTimeStateMachine::timed_exit_state_react(int wait_time_s) {
    if (has_input_just_been_pressed(InputSystem::Input::PAUSE)) {
        controller.restart_timer();
        return true;
    }

    return timed_state_react(wait_time_s);
}

bool BurgerTimeStateMachine::timed_state_react(int wait_time_s) {
    auto elapsed_time = controller.get_elapsed_time();
    if (elapsed_time.asSeconds() >= wait_time_s) {
        controller.restart_timer();
        return true;
    }

    return false;
}


void HighscoreDisplayScreenState::entry() {
    controller.clear_screen();

    auto burger_time_text = gui.create_text("hScoreBurTime", "BURGER TIME",
                                            sf::Vector2u(280, 150),
                                            sf::Vector2f(0.70, 0.70),
                                            sf::Color::Red);

    auto best_five_players_text = gui.create_text("hScoreBestFivePlayers",
                                  "BEST FIVE PLAYERS",
                                  sf::Vector2u(180, 300),
                                  sf::Vector2f(0.70, 0.70));


    HighScores high_scores;
    auto h_scores = high_scores.get_high_scores();

    for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i) {
        auto score_str = std::to_string(h_scores[i].second);

        std::string text = std::to_string(i + 1) + " " + h_scores[i].first.data()
                           + GUI::fix_text_to_right(score_str, MAX_SCORE_CHARS) + " PTS";

        auto h_score_text = gui.create_text(std::string("hScorehScoreText")
                                            + std::to_string(i), text,
                                            sf::Vector2u(180, (450 + i * 100)),
                                            sf::Vector2f(0.70, 0.70));

        controller.add_drawable(h_score_text);
    }

    controller.add_drawable(burger_time_text);
    controller.add_drawable(best_five_players_text);
    controller.restart_timer();
}

void HighscoreDisplayScreenState::react(const ExecuteEvent &) {
    if (BurgerTimeStateMachine::timed_exit_state_react(5)) {
        transit<ItemPointsScreenState>();
    }
}


void ItemPointsScreenState::entry() {
    controller.clear_screen();

    auto burger_time_text = gui.create_text("itemPointsBurTime", "BURGER TIME",
                                            sf::Vector2u(280, 150),
                                            sf::Vector2f(0.70, 0.70),
                                            sf::Color::Red);

    auto score_text = gui.create_text("itemPointsScore", "-SCORE-",
                                      sf::Vector2u(340, 230), sf::Vector2f(0.70, 0.70));

    top_bun[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*top_bun[0], BtSprites::Sprite::TOP_BREAD_1);
    top_bun[0]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    top_bun[0]->setScale(2, 2);

    top_bun[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*top_bun[1], BtSprites::Sprite::TOP_BREAD_2);
    top_bun[1]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    top_bun[1]->move(16, 0);
    top_bun[1]->setScale(2, 2);

    top_bun[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*top_bun[2], BtSprites::Sprite::TOP_BREAD_3);
    top_bun[2]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    top_bun[2]->move(2 * 16, 0);
    top_bun[2]->setScale(2, 2);

    top_bun[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*top_bun[3], BtSprites::Sprite::TOP_BREAD_4);
    top_bun[3]->setPosition(20 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    top_bun[3]->move(3 * 16, 0);
    top_bun[3]->setScale(2, 2);

    lettuce[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*lettuce[0], BtSprites::Sprite::LETTUCE_1);
    lettuce[0]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[0]->setScale(2, 2);

    lettuce[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*lettuce[1], BtSprites::Sprite::LETTUCE_2);
    lettuce[1]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[1]->move(16, 0);
    lettuce[1]->setScale(2, 2);

    lettuce[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*lettuce[2], BtSprites::Sprite::LETTUCE_3);
    lettuce[2]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[2]->move(2 * 16, 0);
    lettuce[2]->setScale(2, 2);

    lettuce[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*lettuce[3], BtSprites::Sprite::LETTUCE_4);
    lettuce[3]->setPosition(35 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    lettuce[3]->move(3 * 16, 0);
    lettuce[3]->setScale(2, 2);

    cheese[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*cheese[0], BtSprites::Sprite::CHEESE_1);
    cheese[0]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[0]->setScale(2, 2);

    cheese[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*cheese[1], BtSprites::Sprite::CHEESE_2);
    cheese[1]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[1]->move(16, 0);
    cheese[1]->setScale(2, 2);

    cheese[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*cheese[2], BtSprites::Sprite::CHEESE_3);
    cheese[2]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[2]->move(2 * 16, 0);
    cheese[2]->setScale(2, 2);

    cheese[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*cheese[3], BtSprites::Sprite::CHEESE_4);
    cheese[3]->setPosition(50 * WINDOW_WIDTH / 100, 38 * WINDOW_HEIGHT / 100);
    cheese[3]->move(3 * 16, 0);
    cheese[3]->setScale(2, 2);


    burger[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*burger[0], BtSprites::Sprite::BURGER_1);
    burger[0]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[0]->setScale(2, 2);

    burger[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*burger[1], BtSprites::Sprite::BURGER_2);
    burger[1]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[1]->move(16, 0);
    burger[1]->setScale(2, 2);

    burger[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*burger[2], BtSprites::Sprite::BURGER_3);
    burger[2]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[2]->move(2 * 16, 0);
    burger[2]->setScale(2, 2);

    burger[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*burger[3], BtSprites::Sprite::BURGER_4);
    burger[3]->setPosition(20 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    burger[3]->move(3 * 16, 0);
    burger[3]->setScale(2, 2);

    tomato[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*tomato[0], BtSprites::Sprite::TOMATO_1);
    tomato[0]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[0]->setScale(2, 2);

    tomato[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*tomato[1], BtSprites::Sprite::TOMATO_2);
    tomato[1]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[1]->move(16, 0);
    tomato[1]->setScale(2, 2);

    tomato[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*tomato[2], BtSprites::Sprite::TOMATO_3);
    tomato[2]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[2]->move(2 * 16, 0);
    tomato[2]->setScale(2, 2);

    tomato[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*tomato[3], BtSprites::Sprite::TOMATO_4);
    tomato[3]->setPosition(35 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    tomato[3]->move(3 * 16, 0);
    tomato[3]->setScale(2, 2);

    bot_bun[0] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*bot_bun[0], BtSprites::Sprite::BOTTOM_BREAD_1);
    bot_bun[0]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    bot_bun[0]->setScale(2, 2);

    bot_bun[1] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*bot_bun[1], BtSprites::Sprite::BOTTOM_BREAD_2);
    bot_bun[1]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    bot_bun[1]->move(16, 0);
    bot_bun[1]->setScale(2, 2);

    bot_bun[2] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*bot_bun[2], BtSprites::Sprite::BOTTOM_BREAD_3);
    bot_bun[2]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    bot_bun[2]->move(2 * 16, 0);
    bot_bun[2]->setScale(2, 2);

    bot_bun[3] = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*bot_bun[3], BtSprites::Sprite::BOTTOM_BREAD_4);
    bot_bun[3]->setPosition(50 * WINDOW_WIDTH / 100, 45 * WINDOW_HEIGHT / 100);
    bot_bun[3]->move(3 * 16, 0);
    bot_bun[3]->setScale(2, 2);

    auto fifty_pts_text = gui.create_text("itemPointsFiftyPts", "50 PTS",
                                          sf::Vector2u(670, 410),
                                          sf::Vector2f(0.70, 0.70));

    ice_cream = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*ice_cream, BtSprites::Sprite::ICE_CREAM);
    ice_cream->setPosition(20 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    ice_cream->setScale(2, 2);

    pt_500 = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*pt_500, BtSprites::Sprite::P_500);
    pt_500->setPosition(20 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt_500->setScale(2, 2);

    coffee = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*coffee, BtSprites::Sprite::COFFEE);
    coffee->setPosition(30 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    coffee->setScale(2, 2);

    pt_1000 = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*pt_1000, BtSprites::Sprite::P_1000);
    pt_1000->setPosition(30 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt_1000->setScale(2, 2);

    fries = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*fries, BtSprites::Sprite::FRIES);
    fries->setPosition(40 * WINDOW_WIDTH / 100, 55 * WINDOW_HEIGHT / 100);
    fries->setScale(2, 2);

    pt_1500 = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*pt_1500, BtSprites::Sprite::P_1500);
    pt_1500->setPosition(40 * WINDOW_WIDTH / 100, 62 * WINDOW_HEIGHT / 100);
    pt_1500->setScale(2, 2);

    auto bonus_pepper_text = gui.create_text("itemPointsBonusPepper", "-BONUS 1",
                             sf::Vector2u(480, 580),
                             sf::Vector2f(0.70, 0.70));

    pepper = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*pepper, BtSprites::Sprite::PEPPER);
    pepper->setPosition(80 * WINDOW_WIDTH / 100, 58 * WINDOW_HEIGHT / 100);
    pepper->setScale(2, 2);

    auto bonus_life_text = gui.create_text("itemPointsBonusLife",
                                           "BONUS  FOR EVERY 20000PTS",
                                           sf::Vector2u(30, 800),
                                           sf::Vector2f(0.70, 0.70));

    chef = std::make_shared<sf::Sprite>();
    BtSprites::set_initial_sprite(*chef, BtSprites::Sprite::PLAYER_STILL_FRONT);
    chef->setPosition(22 * WINDOW_WIDTH / 100, 78 * WINDOW_HEIGHT / 100);
    chef->setScale(2, 2);

    controller.add_drawable(burger_time_text);
    controller.add_drawable(score_text);
    controller.add_drawable(top_bun[0]);
    controller.add_drawable(top_bun[1]);
    controller.add_drawable(top_bun[2]);
    controller.add_drawable(top_bun[3]);
    controller.add_drawable(lettuce[0]);
    controller.add_drawable(lettuce[1]);
    controller.add_drawable(lettuce[2]);
    controller.add_drawable(lettuce[3]);
    controller.add_drawable(cheese[0]);
    controller.add_drawable(cheese[1]);
    controller.add_drawable(cheese[2]);
    controller.add_drawable(cheese[3]);
    controller.add_drawable(burger[0]);
    controller.add_drawable(burger[1]);
    controller.add_drawable(burger[2]);
    controller.add_drawable(burger[3]);
    controller.add_drawable(tomato[0]);
    controller.add_drawable(tomato[1]);
    controller.add_drawable(tomato[2]);
    controller.add_drawable(tomato[3]);
    controller.add_drawable(bot_bun[0]);
    controller.add_drawable(bot_bun[1]);
    controller.add_drawable(bot_bun[2]);
    controller.add_drawable(bot_bun[3]);
    controller.add_drawable(fifty_pts_text);
    controller.add_drawable(ice_cream);
    controller.add_drawable(pt_500);
    controller.add_drawable(coffee);
    controller.add_drawable(pt_1000);
    controller.add_drawable(fries);
    controller.add_drawable(pt_1500);
    controller.add_drawable(bonus_pepper_text);
    controller.add_drawable(pepper);
    controller.add_drawable(bonus_life_text);
    controller.add_drawable(chef);
    controller.restart_timer();
}

void ItemPointsScreenState::react(const ExecuteEvent &) {
    if (BurgerTimeStateMachine::timed_exit_state_react(5)) {
        transit<MainScreenState>();
    }
}

void MainScreenState::entry() {
    MainScreenStateMachine::reset();
    MainScreenStateMachine::start();
}

void MainScreenState::react(const ExecuteEvent &event) {
    MainScreenStateMachine::dispatch(event);

    if (MainScreenStateMachine::is_in_state<FinishedStartState>()) {
        transit<PlayingState>();
    }

    if (MainScreenStateMachine::is_in_state<FinishedExitState>()) {
        transit<FinishedState>();
    }
}

void PlayingState::entry() {
    PlayingStateMachine::reset();
    PlayingStateMachine::start();
}

void PlayingState::react(const ExecuteEvent &event) {
    if (PlayingStateMachine::is_in_state<GameOverStatePlaying>()) {
        HighScores hscores;
        if (hscores.is_high_score(PlayingStateMachine::get_current_score())) {
            transit<EnterHighscoreState>();
        }
        else {
            transit<GameOverScreenState>();
        }
    }
    else {
        PlayingStateMachine::dispatch(event);
    }
}

constexpr std::array<const char *, GameOverScreenState::MAX_TEXTS> GameOverScreenState::DIFFERENT_TEXTS;

void GameOverScreenState::entry() {
    controller.clear_screen();

    auto text = gui.create_text("gameOverText", DIFFERENT_TEXTS[0], sf::Vector2u(300, 500), sf::Vector2f(0.8, 0.8));

    controller.add_drawable(text);
    current_text = 1;
    controller.restart_timer();
}

void GameOverScreenState::react(const ExecuteEvent &) {
    auto elapsed_time = controller.get_elapsed_time();

    if (current_text == MAX_TEXTS) {
        if (elapsed_time.asSeconds() >= 1) {
            transit<MainScreenState>();
            return;
        }
    }
    else if (elapsed_time.asSeconds() >= ANIMATION_FREQ) {
        auto text = gui.get_text("gameOverText").lock();
        text->setString(DIFFERENT_TEXTS[current_text]);
        current_text++;
        controller.restart_timer();
    }
}


uint32_t EnterHighscoreState::new_high_score;

void EnterHighscoreState::entry() {
    set_high_score(PlayingStateMachine::get_current_score());
    char_position = 0;
    controller.clear_screen();

    auto burger_time_text = gui.create_text("enterHighScoreBurTime", "BURGER TIME",
                                            sf::Vector2u(280, 150),
                                            sf::Vector2f(0.7, 0.7),
                                            sf::Color::Red);

    auto help_text = gui.create_text("enterHighScoreHelp", ENTER_NAME_STR,
                                     sf::Vector2u(220, 300), sf::Vector2f(0.7, 0.7));

    HighScores high_scores;
    auto hScores = high_scores.get_high_scores();

    high_score_position = high_scores.high_score_position(new_high_score) - 1;
    bool has_written_new_score = false;

    for (int i = 0; i < HighScores::NUM_HIGH_SCORES; ++i) {
        uint32_t high_score;
        std::string player_name;
        if (i == high_score_position) {
            high_score = new_high_score;
            player_name = "_  ";
            has_written_new_score = true;
        }
        else {
            int pos = i;
            if (has_written_new_score) {
                pos -= 1;
            }
            high_score = hScores[pos].second;
            player_name = hScores[pos].first.data();
        }

        auto score_str = gui.fix_text_to_right(std::to_string(high_score),
                                               MAX_SCORE_CHARS);

        auto h_score_text = gui.create_text(HIGH_SCORE_TEXT_BASE + std::to_string(i),
                                            std::to_string(i + 1) + " " +
                                            player_name + score_str +
                                            " PTS",
                                            sf::Vector2u(180, (450 + i * 100)),
                                            sf::Vector2f(0.7, 0.7));

        controller.add_drawable(h_score_text.lock());
    }

    controller.add_drawable(burger_time_text);
    controller.add_drawable(help_text);
    controller.restart_timer();
}

void EnterHighscoreState::react(const ExecuteEvent &) {
    auto help_text = gui.get_text("enterHighScoreHelp").lock();

    auto new_high_score_text = gui.get_text(HIGH_SCORE_TEXT_BASE +
                                            std::to_string(high_score_position)).lock();

    auto current_str = new_high_score_text->getString();
    if (char_position > 0 &&
            InputSystem::has_input_just_been_pressed(InputSystem::Input::DELETE)) {

        if (char_position < HighScores::PLAYER_NAME_SIZE - 1) {
            current_str[2 + char_position] = ' ';
        }

        char_position--;
        current_str[2 + char_position] = '_';
    }

    if (char_position < HighScores::PLAYER_NAME_SIZE - 1 && InputSystem::has_entered_text()) {
        char new_char = InputSystem::get_current_char();
        current_str[2 + char_position] = new_char;
        if (char_position < HighScores::PLAYER_NAME_SIZE - 2) {
            current_str[2 + char_position + 1] = '_';
        }
        char_position++;
    }

    if (char_position == HighScores::PLAYER_NAME_SIZE - 1) {
        Audio::play(Audio::Track::ENTRY_SELECTED);
        help_text->setString("CONFIRM? (ENTER)");
        help_text->setPosition(18 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
        if (InputSystem::has_input_just_been_pressed(InputSystem::Input::ENTER_MENU)) {
            HighScores highScores;
            highScores.save_new_score(current_str.substring(2, 4), new_high_score);
            transit<MainScreenState>();
        }
    }
    else {
        help_text->setString(ENTER_NAME_STR);
        help_text->setPosition(22 * WINDOW_WIDTH / 100, 30 * WINDOW_HEIGHT / 100);
    }


    new_high_score_text->setString(current_str);
}

void EnterHighscoreState::set_high_score(uint32_t high_score) {
    new_high_score = high_score;
}
