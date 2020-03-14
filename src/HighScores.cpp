#include "HighScores.hpp"
#include <fstream>
#include <cstdint>

constexpr std::array<std::pair<const char*, uint32_t>, HighScores::NUM_HIGH_SCORES> HighScores::DEFAULT_SCORES;

HighScores::HighScores(const std::string &fileName)
{
    this->fileName = fileName;

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

    // TODO: sort highScores
}

std::array<std::pair<std::array<char, 4>, uint32_t>, HighScores::NUM_HIGH_SCORES> HighScores::getHighScores() const
{
    return highScores;
}


void HighScores::createDefaultScores()
{
    std::ofstream file;
    file.open(fileName);

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
