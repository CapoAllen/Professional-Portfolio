#pragma once

#include "GameObject.h"
#include <vector>

class Game {
private:
    int width;
    int height;
    int numDeadBlocks;
    int hitBlock;
    std::vector<std::vector<GameObject*>> gameboard;
    UserPlayer player;
    GameObject block;
    GameObject deadBlock;

public:
    Game(UserPlayer p_, GameObject b_);
    void printGameBoard();
    void playGame();
};
