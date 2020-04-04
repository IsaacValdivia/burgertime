#include "HighScores.hpp"
#include "Constants.hpp"
#include <fstream>
#include <cstdint>
#include <algorithm>

constexpr std::array<std::pair<const char*, uint32_t>, HighScores::NUM_HIGH_SCORES> HighScores::DEFAULT_SCORES;

HighScores::HighScores()
: fileName(HSCORE_FILE)
{
    std::ifstream file;
    file.open(fileName, std::ios::binary);

    if (!file)
    {
        createDefaultScores();
        return;
    }

    for (int i = 0; i < NUM_HIGH_SCORES; ++i)
    {
        std::array<char, PLAYER_NAME_SIZE> playerName;
        file.read(playerName.data(), PLAYER_NAME_SIZE);

        if (!file)
        {
            createDefaultScores();
            return;
        }

        uint32_t score;
        file.read(reinterpret_cast<char*>(&score), sizeof(score));

        if (!file)
        {
            createDefaultScores();
            return;
        }

        highScores[i] = std::make_pair(playerName, score);
    }

    std::sort(highScores.begin(), highScores.end(), [](const std::pair<std::array<char, 4>, uint32_t> &left, const std::pair<std::array<char, 4>, uint32_t> &right) {
        return left.second > right.second;
    });
}

std::array<std::pair<std::array<char, 4>, uint32_t>, HighScores::NUM_HIGH_SCORES> HighScores::getHighScores() const
{
    return highScores;
}


void HighScores::createDefaultScores()
{
    std::ofstream file;
    file.open(fileName, std::ios::binary);

    if (!file)
    {
        // TODO: throw exception
    }

    for (int i = 0; i < NUM_HIGH_SCORES; ++i)
    {
        std::array<char, PLAYER_NAME_SIZE> playerName;
        for (uint8_t j = 0; j < PLAYER_NAME_SIZE; ++j)
        {
            playerName[j] = DEFAULT_SCORES[i].first[j];
        }

        file.write(DEFAULT_SCORES[i].first, PLAYER_NAME_SIZE);
        file.write(reinterpret_cast<const char*>(&DEFAULT_SCORES[i].second), sizeof(DEFAULT_SCORES[i].second));
        highScores[i].first = playerName;
        highScores[i].second = DEFAULT_SCORES[i].second;
    }
}

bool HighScores::isHighScore(uint32_t score) const
{
    return score >= highScores[NUM_HIGH_SCORES - 1].second; 
}

int HighScores::highScorePosition(uint32_t score) const
{
    for (int i = 0; i < NUM_HIGH_SCORES; ++i)
    {
        if (score >= highScores[i].second)
        {
            return i + 1;
        }
    }

    return 0;
}


uint32_t HighScores::getTopScore() const
{
    return highScores[0].second;
}


void HighScores::saveNewScore(const std::string &playerName, uint32_t newHscore)
{
    std::vector<std::pair<std::array<char, 4>, uint32_t>> hScores;

    std::array<char, 4> plName;
    std::copy(std::begin(playerName), std::end(playerName), std::begin(plName));
    plName.back() = '\0';
    hScores.push_back(std::make_pair(plName, newHscore));

    std::copy(std::begin(highScores), std::end(highScores), std::back_inserter(hScores));
    std::sort(hScores.begin(), hScores.end(), [](const std::pair<std::array<char, 4>, uint32_t> &left, const std::pair<std::array<char, 4>, uint32_t> &right) {
        return left.second > right.second;
    });

    std::ofstream file;
    file.open(fileName, std::ios::binary);
    for (int i = 0; i < NUM_HIGH_SCORES; ++i)
    {
        std::array<char, PLAYER_NAME_SIZE> playerName;
        for (uint8_t j = 0; j < PLAYER_NAME_SIZE; ++j)
        {
            playerName[j] = DEFAULT_SCORES[i].first[j];
        }

        file.write(hScores[i].first.cbegin(), PLAYER_NAME_SIZE);
        file.write(reinterpret_cast<const char*>(&hScores[i].second), sizeof(hScores[i].second));
    }
}
