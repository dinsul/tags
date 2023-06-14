#include "game.h"

int main()
{
    int field[4][4];

    init(field);
    GameState cur_state;

    do
    {
        drawScreen(field);
        cur_state = getState();
        doAction(field, cur_state);
    }
    while(cur_state != GameState::EXIT);

    close();

    return 0;
}
