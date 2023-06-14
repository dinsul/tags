#include "helpers.h"
#include <stdio.h>
#include <unistd.h>

DrawerSimple::DrawerSimple(Game *game)
{ 
    tcgetattr(STDIN_FILENO, &_oldt);
    termios _newt = _oldt;

    _newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &_newt);
};

DrawerSimple::~DrawerSimple()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &_oldt);
}

void DrawerSimple::drawScreen(Game *game)
{
    printf("\033[H\033[J");
    for (uint16_t x = 0; x < game->getRows() * 2 + 1; ++x)
    {
        if (x % 2 == 0)
        {
            printf("-------------\n");
        }
        else
        {
            for (uint16_t y = 0; y < game->getColumns(); ++y)
            {
                if (game->getCellValue(x/2, y) == 0)
                {
                    printf("|  ");
                }
                else
                {
                    printf("|%.2d", game->getCellValue(x/2, y));
                }
            }
            printf("|\n");
        }
    }
}
