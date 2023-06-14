#include <termios.h>
#include "../game.h"

class DrawerSimple: public DrawHelper
{
    termios _oldt;
public:
    DrawerSimple(Game *game);
    ~DrawerSimple();

    virtual void drawScreen(Game *game) final;
};
