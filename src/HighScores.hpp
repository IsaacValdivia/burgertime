#pragma once

#include <utility>
#include <array>
#include <string>
#include <vector>

class HighScores
{
public:
    static constexpr auto NUM_HIGH_SCORES = 5;
    static constexpr auto PLAYER_NAME_SIZE = 4;

    HighScores();

    std::array<std::pair<std::array<char, 4>, uint32_t>, NUM_HIGH_SCORES> getHighScores() const;

    bool isHighScore(uint32_t score) const;

    int highScorePosition(uint32_t score) const;

    uint32_t getTopScore() const;

    void saveNewScore(const std::string &playerName, uint32_t newHscore);

private:
    void createDefaultScores();

    static constexpr std::array<std::pair<const char *, uint32_t>, NUM_HIGH_SCORES> DEFAULT_SCORES = {
        std::make_pair("AA1", 10000),
        std::make_pair("AA2", 1000),
        std::make_pair("AA3", 100),
        std::make_pair("AA4", 10),
        std::make_pair("AA5", 1),
    };

    const std::string fileName;
    std::array<std::pair<std::array<char, 4>, uint32_t>, NUM_HIGH_SCORES> highScores;
};
