#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>

Game::Game(UserPlayer p_, GameObject b_)
    : width(10), height(10), numDeadBlocks(10), player(p_), block(b_)
{
    int hitBlock = 0;

    deadBlock.setSymbol('-');

    gameboard.resize(height, std::vector<GameObject*>(width, &block));

    gameboard[player.getY()][player.getX()] = &player;

    for (int i = 0; i < numDeadBlocks; i++) {
        int x = rand() % width;
        int y = rand() % height;
        gameboard[y][x] = &deadBlock;
    }
}

void Game::printGameBoard() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << gameboard[y][x]->getSymbol();
        }
        std::cout << "\033[32m" << std::endl;
    }
}

void Game::playGame() {
    char input;

    while (true) {
        
        printGameBoard();
        std::cout << "\033[0m" << "Enter a move (wasd) or (q) to quit: ";
         input =_getch();


        if (input == 'q') return;

        gameboard[player.getY()][player.getX()] = &block;

        player.move(input, width - 1, height - 1);

        if (gameboard[player.getY()][player.getX()] == &deadBlock) {
            hitBlock++;
            std::cout <<  "Dead block hit: " << hitBlock << std::endl;
        }

        gameboard[player.getY()][player.getX()] = &player;

        if (player.getX() == width - 1 && player.getY() == height - 1) {
            std::cout << " YOU WIN " << std::endl;
            return;
        }

      
    }
}
