#include "Map.hpp"

#include <fstream>
#include <iostream>

std::vector<std::string> Map::process_mapfile(const std::string &filename) const {
    std::ifstream f;
    f.open(filename);

    if (f.is_open()) {
        std::vector<std::string> rows;
        char row_aux[MAX_COLS + 1];
        std::string row;
        while (!f.eof()) {
            f.getline(row_aux, MAX_COLS + 1);
            row = row_aux;
            int s = row.size();
            if (s != MAX_COLS) {
                throw std::runtime_error("Rows can only have " + std::to_string(MAX_COLS) + " tiles");
            }
            rows.push_back(row);
        }
        f.close();
        return rows;
    }
    else {
        throw std::runtime_error("File " + filename + " could not be found");
    }
}

void Map::fill_tiles(const std::vector<std::string> &map_data) {
    unsigned int i = 0, j;
    bool double_placed = false;
    for (auto &row : map_data) {
        j = 0;
        for (auto &content : row) {
            float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
            float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
            if (content == Tile::STAIRS || content == Tile::GO_UP || content == Tile::GO_DOWN ||
                    content == Tile::GO_BOTH || content == Tile::BASKET_EDGE) {

                double_placed = !double_placed;
            }
            tile_data[i][j] = std::make_shared<Tile>(x, y, i, j, static_cast<Tile::Type>(content), double_placed);
            ++j;
        }
        ++i;
    }
}

void Map::fill_ingredients(const std::vector<std::string> &map_data) {
    unsigned int i = 0, j;
    for (auto &row : map_data) {
        j = 0;
        unsigned int ing_found = 0;
        for (auto &content : row) {
            if (content != Ingredient::NOT_ING) {
                if (is_enemy(content)) {
                    enemy_spawns.push_front(std::make_pair(static_cast<Enemy::Type>(content), sf::Vector2u(i, j)));
                }
                else if (is_item(content)) {
                    item_spawn.first = static_cast<Map::SpecialItem>(content);
                    item_spawn.second = sf::Vector2u(i, j);
                }
                else if (is_chef(content)) {
                    chef_spawn = sf::Vector2u(i, j);
                }
                else {
                    if (ing_found <= 0) {
                        if ((Ingredient::Type)content == Ingredient::Type::TOP_BUN) {
                            ++num_burgers;
                        }
                        float x = SIDE_MARGINS + j * Tile::TILE_WIDTH;
                        float y = UPPER_MARGIN + i * Tile::TILE_HEIGHT;
                        ing_data.emplace_back(x, y, (Ingredient::Type)content);
                    }
                    ing_found = (ing_found + 1) % 4;
                }
            }
            ++j;
        }
        ++i;
    }
}

bool Map::horizontal_platform_check(const Tile &t) const {
    return t.is_floor() || t.is_go_up() || t.is_go_down() || t.is_go_both();
}

bool Map::vertical_platform_check(const Tile &t) const {
    return t.is_stairs() || t.is_go_up() || t.is_go_down() || t.is_go_both();
}

bool Map::right_platform_check(const Tile &t) const {
    return t.get_col() < (MAX_COLS - 1) &&
           tile_data[t.get_row()][t.get_col() + 1]->is_steppable_hor();
}

bool Map::left_platform_check(const Tile &t) const {
    return t.get_col() > 0 &&
           tile_data[t.get_row()][t.get_col() - 1]->is_steppable_hor();
}

bool Map::up_platform_check(const Tile &t) const {
    return t.get_row() > 0 &&
           tile_data[t.get_row() - 1][t.get_col()]->is_steppable_vert();
}

bool Map::down_platform_check(const Tile &t) const {
    return t.get_row() < (MAX_ROWS - 1) &&
           tile_data[t.get_row() + 1][t.get_col()]->is_steppable_vert();
}

bool Map::can_move_right(const Tile &t) const {
    // check if platform allows the movement, and also right platform
    return horizontal_platform_check(t) && right_platform_check(t);
}

bool Map::can_move_left(const Tile &t) const {
    // check if platform allows the movement, and also left platform
    return horizontal_platform_check(t) && left_platform_check(t);
}

bool Map::can_move_up(const Tile &t) const {
    // check if platform allows the movement, and also top platform
    return vertical_platform_check(t) && up_platform_check(t);
}

bool Map::can_move_down(const Tile &t) const {
    // check if platform allows the movement, and also bottom platform
    return vertical_platform_check(t) && down_platform_check(t);
}

bool Map::can_move_right(const Tile &t, float right_edge) const {
    // check if platform allows the movement
    if (horizontal_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (right_platform_check(t)) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.get_position().x + Tile::TILE_WIDTH;
        if (right_edge < tile_edge) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Map::can_move_left(const Tile &t, float left_edge) const {
    // check if platform allows the movement
    if (horizontal_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (left_platform_check(t)) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.get_position().x;
        if (left_edge > tile_edge) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Map::can_move_up(const Tile &t, float top_edge) const {
    // check if platform allows the movement
    if (vertical_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (up_platform_check(t)) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.get_position().y + 14;
        if (top_edge > tile_edge) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Map::can_move_down(const Tile &t, float bot_edge) const {
    // check if platform allows the movement
    if (vertical_platform_check(t)) {
        // if next tile also allows hor movement, true
        if (down_platform_check(t)) {
            return true;
        }
        // if end of tile has not been reached, true
        float tile_edge = t.get_position().y + Tile::TILE_HEIGHT - t.get_height();
        if (bot_edge < tile_edge) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool Map::is_enemy(const char c) {
    return c == Enemy::Type::SAUSAGE || c == Enemy::Type::EGG || c == Enemy::Type::PICKLE;
}

bool Map::is_item(const char c) {
    return c == ICE_CREAM || c == COFFEE || c == FRIES;
}

bool Map::is_chef(const char c) {
    return c == CHEF;
}

Map::Map(const std::string &map_file) {
    fill_tiles(process_mapfile(map_file + MAP_EXTENSION));
    fill_ingredients(process_mapfile(map_file + INGMAP_EXTENSION));
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto &row : tile_data) {
        for (auto &tile : row) {
            target.draw(*tile, states);
        }
    }
    for (auto &ing : ing_data) {
        target.draw(ing, states);
    }
}

std::vector<std::shared_ptr<Tile>> Map::entity_on_tiles(const Entity &entity) const {
    auto collision_shape = entity.get_collision_shape();
    float bot_left_x = collision_shape.left;
    float bot_right_x = collision_shape.left + collision_shape.width;
    float bot_y = collision_shape.top + collision_shape.height;

    std::vector<std::shared_ptr<Tile>> tiles;

    // Check left_edge
    size_t horizontal_tile_1 = (bot_left_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check right_edge
    size_t horizontal_tile_2 = (bot_right_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check upper_edge
    size_t vertical_tile = (bot_y - (UPPER_MARGIN + 1)) / Tile::TILE_HEIGHT;

    if (vertical_tile >= MAX_ROWS) {
        return tiles;
    }
    for (int h_i = horizontal_tile_1; h_i < horizontal_tile_2 + 1; ++h_i) {
        if (!tile_data[vertical_tile][h_i]->is_empty()) {
            tiles.push_back(tile_data[vertical_tile][h_i]);
        }
    }

    return tiles;
}

bool Map::can_entity_move(float &x, float &y, const Entity &entity) const {
    const auto &collision_shape = entity.get_collision_shape();
    float bot_left_x = collision_shape.left;
    float bot_right_x = collision_shape.left + collision_shape.width;

    float bot_y = collision_shape.top + collision_shape.height;

    std::vector<std::shared_ptr<Tile>> tiles_of_entity = entity_on_tiles(entity);

    bool horizontal_mov = x != 0;
    bool up = false, right = false;

    if (horizontal_mov) {
        right = x > 0.0;
    }
    else {
        up = y < 0.0;
    }

    if (horizontal_mov && (right && can_move_right(*tiles_of_entity.back(), bot_right_x) || !right && can_move_left(*tiles_of_entity.front(), bot_left_x))) {
        y = ((tiles_of_entity[0]->get_position().y + Tile::TILE_HEIGHT) -
             tiles_of_entity[0]->get_height()) - bot_y;
        return true;
    }
    else {
        short up_bot_count = 0;
        for (const auto &tile : tiles_of_entity) {
            if (!horizontal_mov && (up && can_move_up(*tile, bot_y) || !up && can_move_down(*tile, bot_y))) {
                if (tile->is_steppable_vert_left()) {
                    x = (tile->get_position().x + Tile::TILE_WIDTH) -
                        ((bot_right_x + bot_left_x) / 2.0);
                } else if (tile->is_steppable_vert_right()) {
                    x = (tile->get_position().x) -
                        ((bot_right_x + bot_left_x) / 2.0);
                }
                ++up_bot_count;
            }
        }

        if (up_bot_count == tiles_of_entity.size()) {
            return true;
        }
    }

    return false;
}

bool Map::out_of_map(const Actor &actor) const {
    auto collision_shape = actor.get_collision_shape();

    float bot_left_x = collision_shape.left;
    float bot_right_x = collision_shape.left + collision_shape.width;

    // Check left_edge
    float horizontal_tile_1 = (bot_left_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    // Check right_edge
    float horizontal_tile_2 = (bot_right_x - (SIDE_MARGINS + 1)) / Tile::TILE_WIDTH;

    if (horizontal_tile_1 < 0.0 || horizontal_tile_2 >= MAX_COLS) {
        return true;
    }

    return false;
}

std::vector<std::shared_ptr<const Tile>> Map::available_from(const Tile &current) const {
    std::vector<std::shared_ptr<const Tile>> available_paths;

    if (can_move_up(current)) {
        available_paths.push_back(tile_data[current.get_row() - 1][current.get_col()]);
    }

    if (can_move_down(current)) {
        available_paths.push_back(tile_data[current.get_row() + 1][current.get_col()]);
    }

    if (can_move_left(current)) {
        available_paths.push_back(tile_data[current.get_row()][current.get_col() - 1]);
    }

    if (can_move_right(current)) {
        available_paths.push_back(tile_data[current.get_row()][current.get_col() + 1]);
    }


    return available_paths;
}

std::set<Direction> Map::available_from_direction(const Tile &current,
        const Direction actual_dir) const {

    std::set<Direction> available_paths;

    if (can_move_up(current)) {
        available_paths.insert(Direction::UP);
    }

    if (can_move_down(current)) {
        available_paths.insert(Direction::DOWN);
    }

    if (can_move_left(current)) {
        available_paths.insert(Direction::LEFT);
    }

    if (can_move_right(current)) {
        available_paths.insert(Direction::RIGHT);
    }

    return available_paths;
}

void Map::available_from_direction_inm(const std::shared_ptr<const Tile> &current, 
                    std::vector<std::shared_ptr<const Tile>> &available_paths, int tiles_ahead,
                    const Direction actual_dir) const {
    
    if (tiles_ahead == 0) {
        available_paths.push_back(current);

        return;
    }
    
    if (actual_dir != Direction::DOWN, can_move_up(*current)) {
        const auto &t = tile_data[current->get_row() - 1][current->get_col()];
        available_from_direction_inm(t, available_paths, tiles_ahead - 1, Direction::UP);
    }

    if (actual_dir != Direction::UP && can_move_down(*current)) {
        const auto &t = tile_data[current->get_row() + 1][current->get_col()];
        available_from_direction_inm(t, available_paths, tiles_ahead - 1, Direction::DOWN);
    }

    if (actual_dir != Direction::RIGHT && can_move_left(*current)) {
        const auto &t = tile_data[current->get_row()][current->get_col() - 1];
        available_from_direction_inm(t, available_paths, tiles_ahead - 1, Direction::LEFT);
    }

    if (actual_dir != Direction::LEFT && can_move_right(*current)) {
        const auto &t = tile_data[current->get_row()][current->get_col() + 1];
        available_from_direction_inm(t, available_paths, tiles_ahead - 1, Direction::RIGHT);
    }
}

std::vector<std::shared_ptr<const Tile>> Map::available_from_direction(const std::shared_ptr<const Tile> &current, const Direction actual_dir, 
                                                                       const int tiles_ahead) const
{

    std::vector<std::shared_ptr<const Tile>> available_paths;
    available_from_direction_inm(current, available_paths, tiles_ahead, actual_dir);

    // if (actual_dir != Direction::DOWN && can_move_up(current)) {
    //     Tile &t = tile_data[current.get_row() - 1][current.get_col()]
    //     available_from_direction_inm(t, available_paths, tiles_ahead--, Direction::UP);
    // }

    // if (actual_dir != Direction::UP && can_move_down(current, tiles_ahead)) {
    //     Tile &t = tile_data[current.get_row() + 1][current.get_col()];
    //     available_from_direction_inm(t, available_paths, tiles_ahead--, Direction::DOWN);
    // }

    // if (actual_dir != Direction::RIGHT && can_move_left(current, tiles_ahead)) {
    //     Tile &t = tile_data[current.get_row()][current.get_col() - 1];
    //     available_from_direction_inm(t, available_paths, tiles_ahead--, Direction::LEFT);
    // }

    // if (actual_dir != Direction::LEFT && can_move_right(current, tiles_ahead)) {
    //     Tile &t = tile_data[current.get_row()][current.get_col() + 1];
    //     available_from_direction_inm(t, available_paths, tiles_ahead--, Direction::RIGHT);
    // }

    return available_paths;
}

std::shared_ptr<const Tile> Map::get_chef_initial_tile() const {
    return tile_data[chef_spawn.x][chef_spawn.y];
}

std::shared_ptr<const Tile> Map::get_item_initial_tile() const {
    return tile_data[item_spawn.second.x][item_spawn.second.y];
}

Map::SpecialItem Map::get_item_type() const {
    return item_spawn.first;
}

std::vector<std::pair<Enemy::Type, std::shared_ptr<const Tile>>>
Map::get_enemies_spawns() const {

    std::vector<std::pair<Enemy::Type, std::shared_ptr<const Tile>>> initial_tiles;

    for (const auto &enemy_spawn : enemy_spawns) {
        initial_tiles.push_back(std::make_pair(enemy_spawn.first,
                                               tile_data[enemy_spawn.second.x]
                                               [enemy_spawn.second.y]));
    }

    return initial_tiles;
}

std::vector<Ingredient> &Map::get_ing_data() {
    return ing_data;
}

std::set<Enemy *> Map::enemies_on_tile(const std::shared_ptr<const Tile> &tile) const {
    return old_enemies_positions[tile];
}

std::set<Enemy *> Map::enemies_on_tiles_now(const std::shared_ptr<const Tile> &tile) const {
    return enemies_positions[tile];
}

void Map::reset_enemies_on_tiles() {
    old_enemies_positions = enemies_positions;
    enemies_positions.clear();
}

void Map::set_enemy_on_tile(Enemy *enemy, std::shared_ptr<const Tile> tile) {
    enemies_positions[tile].insert(enemy);
}
