#pragma once
#include <vector>
#include <SFML/Network.hpp>
#include "Log.h"

using namespace sf;

enum Cell {
    EMPTY, 
    PLAYER1,
    PLAYER2
};

class Game
{
public:
    Game();
    ~Game();

    void reset();
    bool isEmpty(int cell);
    bool put(int cell, Cell player);

    void init();
    void start();

    bool hasEmptyCells();
    bool isWinner(Cell player);
private:
    char map1[9];
    char map2[9];

    Log log;

    TcpListener listener;
    TcpSocket player1;
    TcpSocket player2;
};

