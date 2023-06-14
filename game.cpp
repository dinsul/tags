#include <unistd.h>
#include <iostream>

#include "helpers/helpers.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(uint16_t rows, uint16_t columns)
{
    if (rows < 2 || columns < 2)
    {
        std::cerr << "Bad field params" << std::endl;
        return;
    }

    _fieldSize.x = rows;
    _fieldSize.y = columns;

    _field = new uint16_t*[rows];
    for (int i = 0; i < rows; ++i)
    {
        _field[i] = new uint16_t[columns];
    }

    uint16_t i = 0;
    for (uint16_t x = 0; x < rows; ++x)
    {
        for (uint16_t y = 0; y < columns; ++y)
        {
            setCell(x, y, ++i);
        }
    }

    _curPos.x = rows - 1;
    _curPos.y = columns - 1;

    setCell(_curPos.x, _curPos.y, 0);

    _drawer = new DrawerSimple(this);
}

void Game::close()
{
    for (int i = 0; i < _fieldSize.x; ++i)
    {
        delete[] _field[i];
    }

    delete[] _field;

    delete _drawer;
}

GameState Game::getState()
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
    }
    while (true);

    return GameState::UNKNOWN;
}


uint16_t Game::getCellValue(uint16_t row, uint16_t column)
{
    return _field[row][column];
}

void Game::setCell(uint16_t row, uint16_t column, uint16_t value)
{
    _field[row][column] = value;
}

void Game::doAction(GameState state)
{
    switch (state)
    {
    case GameState::MOVE_LEFT:
        if (_curPos.y > 0)
        {
            setCell(_curPos.x, _curPos.y, getCellValue(_curPos.x, _curPos.y - 1));
            setCell(_curPos.x, _curPos.y - 1, 0);
            --_curPos.y;
        }
        break;
    case GameState::MOVE_RIGHT:
        if (_curPos.y < _fieldSize.y - 1)
        {
            _field[_curPos.x][_curPos.y] = _field[_curPos.x][_curPos.y + 1];
            _field[_curPos.x][_curPos.y + 1] = 0;
            ++_curPos.y;
        }
        break;
    case GameState::MOVE_DOWN:
        if (_curPos.x < _fieldSize.x - 1)
        {
            _field[_curPos.x][_curPos.y] = _field[_curPos.x + 1][_curPos.y];
            _field[_curPos.x + 1][_curPos.y] = 0;
            ++_curPos.x;
        }
        break;
    case GameState::MOVE_UP:
        if (_curPos.x > 0)
        {
            _field[_curPos.x][_curPos.y] = _field[_curPos.x - 1][_curPos.y];
            _field[_curPos.x - 1][_curPos.y] = 0;
            --_curPos.x;
        }
        break;
    default:
        break;
    }
}

void Game::refresh()
{
    _drawer->drawScreen(this);
}
