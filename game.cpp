#include <unistd.h>
#include <termios.h>
#include <iostream>

#include "game.h"

static termios g_oldt;
static termios g_newt;

Position g_cur_pos;

void drawScreen(int field[4][4])
{
    printf("\033[H\033[J");
    for (int x = 0; x < 9; ++x)
    {
        if (x % 2 == 0)
        {
            printf("-------------\n");
        }
        else
        {
            for (int y = 0; y < 4; ++y)
            {
                if (field[x/2][y] == 0)
                {
                    printf("|  ");
                }
                else
                {
                    printf("|%.2d", field[x/2][y]);
                }
            }
            printf("|\n");
        }
    }
}

void init(int field[4][4])
{
    tcgetattr(STDIN_FILENO, &g_oldt);
    g_newt = g_oldt;
    g_newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &g_newt);

    int i = 0;
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            field[x][y] = i++;
        }
    }

    g_cur_pos.x = 0;
    g_cur_pos.y = 0;

}

void close()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &g_oldt);
}

GameState getState()
{
    int inter_state = 0;
    int key;

    do
    {
        key = getchar();
        if (inter_state == 0)
        {
            switch (key)
            {
                case 27:
                    inter_state = 1;
                    break;
                case 'q':
                    return GameState::EXIT;
                default:
                    break;
            }
        }
        else if (inter_state == 1)
        {
            switch (key)
            {
                case '[':
                    inter_state = 2;
                    break;
                case 27:
                case 'q':
                    return GameState::EXIT;
                default:
                    inter_state = 0;
                    break;
            }
        }
        else if (inter_state == 2)
        {
            switch (key)
            {
                case 'A':
                    return GameState::MOVE_UP;
                case 'B':
                    return GameState::MOVE_DOWN;
                case 'C':
                    return GameState::MOVE_RIGHT;
                case 'D':
                    return GameState::MOVE_LEFT;
                default:
                    inter_state = 0;
                    break;
            }
        }
        // printf("%d state:%d\n", key, inter_state);
    }
    while (true);

    return GameState::UNKNOWN;
}

void doAction(int field[4][4], GameState state)
{
    switch (state)
    {
    case GameState::MOVE_LEFT:
        if (g_cur_pos.y > 0)
        {
            field[g_cur_pos.x][g_cur_pos.y] = field[g_cur_pos.x][g_cur_pos.y - 1];
            field[g_cur_pos.x][g_cur_pos.y - 1] = 0;
            --g_cur_pos.y;
        }
        break;
    case GameState::MOVE_RIGHT:
        if (g_cur_pos.y < 3)
        {
            field[g_cur_pos.x][g_cur_pos.y] = field[g_cur_pos.x][g_cur_pos.y + 1];
            field[g_cur_pos.x][g_cur_pos.y + 1] = 0;
            ++g_cur_pos.y;
        }
        break;
    case GameState::MOVE_DOWN:
        if (g_cur_pos.x < 3)
        {
            field[g_cur_pos.x][g_cur_pos.y] = field[g_cur_pos.x + 1][g_cur_pos.y];
            field[g_cur_pos.x + 1][g_cur_pos.y] = 0;
            ++g_cur_pos.x;
        }
        break;
    case GameState::MOVE_UP:
        if (g_cur_pos.x > 0)
        {
            field[g_cur_pos.x][g_cur_pos.y] = field[g_cur_pos.x - 1][g_cur_pos.y];
            field[g_cur_pos.x - 1][g_cur_pos.y] = 0;
            --g_cur_pos.x;
        }
        break;
    default:
        break;
    }
}
