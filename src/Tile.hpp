#include <cstdint>

class Tile {
private:
public:
    // Tile codes for regular, inner tiles
    static const char FLOOR = '_';
    static const char GO_UP = '^';
    static const char GO_DOWN = 'v';
    static const char GO_BOTH = '|';
    static const char STAIRS = '#';
    // Tile codes for entry points for enemy NPCs
    static const char ENTRY_N_FLOOR = 'F';
    static const char ENTRY_N_UP = 'U';
    static const char ENTRY_N_DOWN = 'D';
    static const char ENTRY_N_BOTH = 'B';
    // Empty tile (background)
    static const char EMPTY = ' ';
    
    uint8_t col;
    uint8_t row;
    char content;

    Tile();
    Tile(uint8_t _col, uint8_t _row, char _content);

    Tile& operator=(const Tile& other);

    bool isEmpty();
    bool isFloor();
    bool isConnector();
    bool isStairs();
};
