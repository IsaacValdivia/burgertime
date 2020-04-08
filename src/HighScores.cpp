#include "HighScores.hpp"
#include "Constants.hpp"
#include <fstream>
#include <cstdint>
#include <algorithm>

constexpr std::array<std::pair<const char *, uint32_t>,
          HighScores::NUM_HIGH_SCORES> HighScores::DEFAULT_SCORES;

HighScores::HighScores()
    : file_name(HSCORE_FILE) {
    std::ifstream file;
    file.open(file_name, std::ios::binary);

    if (!file) {
        create_default_scores();
        return;
    }

    for (int i = 0; i < NUM_HIGH_SCORES; ++i) {
        std::array<char, PLAYER_NAME_SIZE> player_name;
        file.read(player_name.data(), PLAYER_NAME_SIZE);

        if (!file) {
            create_default_scores();
            return;
        }

        uint32_t score;
        file.read(reinterpret_cast<char *>(&score), sizeof(score));

        if (!file) {
            create_default_scores();
            return;
        }

        high_scores[i] = std::make_pair(player_name, score);
    }

    std::sort(high_scores.begin(), high_scores.end(), [](
                  const std::pair<std::array<char, 4>, uint32_t> &left,
    const std::pair<std::array<char, 4>, uint32_t> &right) {

        return left.second > right.second;
    });
}

std::array<std::pair<std::array<char, 4>, uint32_t>,
HighScores::NUM_HIGH_SCORES> HighScores::get_high_scores() const {

    return high_scores;
}

void HighScores::create_default_scores() {
    std::ofstream file;
    file.open(file_name, std::ios::binary);

    if (!file) {
        // TODO: throw exception
    }

    for (int i = 0; i < NUM_HIGH_SCORES; ++i) {
        std::array<char, PLAYER_NAME_SIZE> player_name;
        for (uint8_t j = 0; j < PLAYER_NAME_SIZE; ++j) {
            player_name[j] = DEFAULT_SCORES[i].first[j];
        }

        file.write(DEFAULT_SCORES[i].first, PLAYER_NAME_SIZE);
        file.write(reinterpret_cast<const char *>(&DEFAULT_SCORES[i].second),
                   sizeof(DEFAULT_SCORES[i].second));

        high_scores[i].first = player_name;
        high_scores[i].second = DEFAULT_SCORES[i].second;
    }
}

bool HighScores::is_high_score(uint32_t score) const {
    return score >= high_scores[NUM_HIGH_SCORES - 1].second;
}

int HighScores::high_score_position(uint32_t score) const {
    for (int i = 0; i < NUM_HIGH_SCORES; ++i) {
        if (score >= high_scores[i].second) {
            return i + 1;
        }
    }

    return 0;
}


uint32_t HighScores::get_top_score() const {
    return high_scores[0].second;
}


void HighScores::save_new_score(const std::string &player_name, uint32_t newHscore) {
    std::vector<std::pair<std::array<char, 4>, uint32_t>> hscores;

    std::array<char, 4> plName;
    std::copy(std::begin(player_name), std::end(player_name), std::begin(plName));
    plName.back() = '\0';
    hscores.push_back(std::make_pair(plName, newHscore));

    std::copy(std::begin(high_scores), std::end(high_scores), std::back_inserter(hscores));

    std::sort(hscores.begin(), hscores.end(), [](
                  const std::pair<std::array<char, 4>, uint32_t> &left,
    const std::pair<std::array<char, 4>, uint32_t> &right) {

        return left.second > right.second;
    });

    std::ofstream file;
    file.open(file_name, std::ios::binary);

    for (int i = 0; i < NUM_HIGH_SCORES; ++i) {
        std::array<char, PLAYER_NAME_SIZE> player_name;
        for (uint8_t j = 0; j < PLAYER_NAME_SIZE; ++j) {
            player_name[j] = DEFAULT_SCORES[i].first[j];
        }

        file.write(hscores[i].first.cbegin(), PLAYER_NAME_SIZE);

        file.write(reinterpret_cast<const char *>(&hscores[i].second),
                   sizeof(hscores[i].second));
    }
}
