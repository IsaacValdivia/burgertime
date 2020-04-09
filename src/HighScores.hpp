#pragma once

#include <array>
#include <string>
#include <utility>
#include <vector>

class HighScores {
public:
    static constexpr auto NUM_HIGH_SCORES = 5;
    static constexpr auto PLAYER_NAME_SIZE = 4;

    /**
     * @brief Construct a new HighScores object
     *
     */
    HighScores();

    /**
     * @brief Get the high scores as an array
     *
     * @return std::array<std::pair<std::array<char, 4>, uint32_t>, NUM_HIGH_SCORES> highscores
     */
    std::array<std::pair<std::array<char, 4>, uint32_t>, NUM_HIGH_SCORES> get_high_scores() const;

    /**
     * @brief Returns if the provided score makes it to the highscores
     *
     * @param score score to check
     * @return true
     * @return false
     */
    bool is_high_score(uint32_t score) const;

    /**
     * @brief Returns the index of the highscore matching score
     *
     * @param score score to check
     * @return int
     */
    int high_score_position(uint32_t score) const;

    /**
     * @brief Returns the top score
     *
     * @return uint32_t
     */
    uint32_t get_top_score() const;

    /**
     * @brief Saves a highscore to a binary file
     *
     * @param player_name name of the player
     * @param new_hscore new highscore
     */
    void save_new_score(const std::string &player_name, uint32_t new_hscore);

private:
    /**
     * @brief Create a Default Scores object
     *
     */
    void create_default_scores();

    static constexpr std::array<std::pair<const char *, uint32_t>, NUM_HIGH_SCORES>
    DEFAULT_SCORES = {

        std::make_pair("AA1", 10000),
        std::make_pair("AA2", 1000),
        std::make_pair("AA3", 100),
        std::make_pair("AA4", 10),
        std::make_pair("AA5", 1),
    };

    const std::string file_name;

    std::array<std::pair<std::array<char, 4>, uint32_t>, NUM_HIGH_SCORES> high_scores;
};
