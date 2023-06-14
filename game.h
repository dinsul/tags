#include <inttypes.h>

enum class GameState
{
    UNKNOWN,
    EXIT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_RIGHT,
    MOVE_LEFT,
};

struct Position
{
    uint16_t x;
    uint16_t y;
};

class Game;

class DrawHelper
{
public:
    virtual ~DrawHelper() {};
    virtual void drawScreen(Game *game) = 0;
};

class Game
{
    uint16_t **_field;
    Position _fieldSize;

    Position _curPos;
    DrawHelper* _drawer;

public:
    Game();
    ~Game();

    void init(uint16_t rows, uint16_t columns);
    void close();
    GameState getState();
    uint16_t getRows()    { return _fieldSize.x; };
    uint16_t getColumns() { return _fieldSize.y; };
    uint16_t getCellValue(uint16_t row, uint16_t column);

    void setCell(uint16_t row, uint16_t column, uint16_t value);

    void doAction(GameState state);
    void refresh();
};
