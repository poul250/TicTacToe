#include "Game.h"

Game::Game()
{
    reset();
}

void Game::reset()
{
    for (int i = 0; i < 9; ++i) {
        map1[i] = map2[i] = 0;
    }
}

bool Game::isEmpty(int cell)
{
    if (cell < 0 || cell >= 9)
        throw "Bad cell number";
    return map1[cell] == EMPTY;
}

bool Game::put(int cell, Cell player)
{
    if (!isEmpty(cell)) {
        return false;
    } else {
        map1[cell] = (player == PLAYER1) - (player == PLAYER2);
        map2[cell] = (player == PLAYER2) - (player == PLAYER1);
        return true;
    }
}

void Game::init()
{
    if (listener.listen(9999) == Socket::Status::Done) {
        log("listening port 9999");
    } else {
        log("Listening err");
        exit(-1);
    }

    if (listener.accept(player1) == sf::Socket::Done) {
        log("accepted player1");
    } else {
        log("accept err");
        exit(-1);
    }

    if (listener.accept(player2) == sf::Socket::Done) {
        log("accepted player2");
    } else {
        log("accept err");
        exit(-1);
    }
}

void Game::start()
{
    init();
    reset();

    Cell winner = EMPTY;
    while (hasEmptyCells()) {
        int cell = 0;
        std::size_t received;
        do {
            player1.send(map1, 9);
            player1.send("\0", 1);
            player1.receive(&cell, 1, received);
            log(std::string("player1 typed ") + std::to_string(cell));
        } while (!put(cell, PLAYER1));

        if (isWinner(PLAYER1)) {
            winner = PLAYER1;
            break;
        }

        if (!hasEmptyCells())
            break;

        do {
            player2.send(map2, 9);
            player2.send("\0", 1);
            player2.receive(&cell, 1, received);
            log(std::string("player2 typed ") + std::to_string(cell));
        } while (!put(cell, PLAYER2));

        if (isWinner(PLAYER2)) {
            winner = PLAYER2;
            break;
        }
    }

    char msg[] = {-1, 0, 1};
    player1.send(map1,    9);
    player1.send(&msg[2], 1);
    player2.send(map2,    9);
    player2.send(&msg[2], 1);

    switch (winner) {
    case PLAYER1:
        player1.send(&msg[2], 1);
        player2.send(&msg[0], 1);
        break;

    case PLAYER2:
        player2.send(&msg[2], 1);
        player1.send(&msg[0], 1);
        break;

    case EMPTY:
        player1.send(&msg[1], 1);
        player2.send(&msg[1], 1);
        break;
    }
    
}

bool Game::hasEmptyCells()
{
    for (int i = 0; i < 9; ++i) 
        if (map1[i] == 0)
            return true;
    return false;
}

bool Game::isWinner(Cell player)
{
    char * map = player == PLAYER1 ? map1 : map2;
    return (map[0] + map[1] + map[2] == 3) ||
        (map[3] + map[4] + map[5] == 3) ||
        (map[6] + map[7] + map[8] == 3) ||
        (map[0] + map[3] + map[6] == 3) ||
        (map[1] + map[4] + map[7] == 3) ||
        (map[2] + map[5] + map[8] == 3) ||
        (map[0] + map[4] + map[8] == 3) ||
        (map[2] + map[4] + map[6] == 3);
}

Game::~Game()
{}
