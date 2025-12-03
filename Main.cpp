#include "GameObject.h"
#include "Game.h"

int main() {
 

    UserPlayer player;
    player.setSymbol('X'); 
    GameObject emptyBlock;
    emptyBlock.setSymbol('-');


    Game game(player, emptyBlock);
    
   
    game.playGame();

    return 0;
}
