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
    int x;
    int y;
};

//class DrawHelper
//{
//public:
    //virtual void init() = 0;
    //virtual void drawScreen() = 0;
//};
//
//
//class Game
//{
    //int **_field;
    //Position _curPos;
    //DrawHelper _drawer;
//
//public:
    //void init();
    //void close();
    //GameState getState();
    //void doAction(GameState state);
//};


void drawScreen(int field[4][4]);
void init(int field[4][4]);
void close();
GameState getState();
void doAction(int field[4][4], GameState state);
