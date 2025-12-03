#include "game.h"
#include <iostream>
#include <cstdlib> // for the rand() function


// Global variables to keep track of the game statistics 
int playerWins = 0;
int dealerWins = 0;
int ties = 0;

void shuffleDeck(std::vector<int>& deck) {
    for (size_t i = 0; i < deck.size(); ++i) {
        size_t randomIndex = rand() % deck.size();
        std::swap(deck[i], deck[randomIndex]);
    }

    // A bit of info about the "rand()" function.
    // Let's say we have this line of code:
    //       int randomChoice = rand() % 3;
    // 
    // This will give us back a random number between 0 and 2. But why?
    // rand() is a function that returns a random int between 0 and the maximum positive int 
    // avaiable (which is 4294967295). To ensure we get a rand number between 0 and a value,
    // we use the mod (%) operator. This is the logic:
    // rand() -> rand() % 3
    //    0   ->  0 % 3 = 0
    //    1   ->  1 % 3 = 1
    //    2   ->  2 % 3 = 2
    //    3   ->  3 % 3 = 0
    //    4   ->  4 % 3 = 1
    //    5   ->  5 % 3 = 2
    //    6   ->  6 % 3 = 0
    //     ............
    //  2542 ->  2542 % 3 = 1
    //  2543 ->  2543 % 3 = 2
    //  2544 ->  2542 % 3 = 0
    //  Do you see the pattern?
}

// TODO (1): Complete the following function 
// (the description is in the header file)
int dealCard(std::vector<int>& deck) {
    // HINT: look up std::vector methods
    int drawnCard = deck.back();  //takes last card from deck
    deck.pop_back();  //removes card from the deck
    return drawnCard; // You may want to change this return value 
}


int playerTurn(std::vector<int>& deck) {
    int playerTotal = 0;
    char choice = ' ';

    std::cout << "Your turn!" << std::endl;

    // Deal the first two cards to the player
    playerTotal += dealCard(deck);
    std::cout << "You drew a " << playerTotal << ". Your total: " << playerTotal << std::endl;
    
    int newCard = dealCard(deck);
    playerTotal += newCard;
    std::cout << "You drew a " << newCard << ". Your total: " << playerTotal << std::endl;
   
    // In the very rare case of drawing two aces (11) 
    if (playerTotal > 21) {
        return playerTotal;
    }

    // TODO (2): Complete the following loop and return the player's total

    // Inside the loop, the player should be asked to 
    // either "hit" (draw a card) or "stay" (keep their current hand).
    // The input for hit is 'h' and for stay is 's'
    
    // The loop continues until the player chooses to stay by entering 's' 
    // or until the player's total exceeds 21 (bust). 

     //loops for players decision to hit or stay
    while (choice != 's' && playerTotal <= 21) {
        std::cout << "Hit (h) or Stay (s): ";
        std::cin >> choice;

        //if player hits
        if (choice == 'h') {
            newCard = dealCard(deck);
            playerTotal += newCard;
            std::cout << "You drew a " << newCard << ". Your total: " << playerTotal << std::endl;

            //if the player busts after hitting
            if (playerTotal > 21) {
                std::cout << "Bust! Your total is over 21." << std::endl;
                break; 
            }
        }
    }

    return playerTotal; // You may want to change this return value 
}


// TODO (3) : Complete the following function
// (the description is in the header file)
int dealerTurn(std::vector<int>& deck) {
   
    // HINT: Complete the previous function first. 
    // The content of this function is very similar to the previous one.
    int dealerTotal = 0;

    std::cout << "Dealer's turn!" << std::endl;

    // Dealer starts with two cards
    dealerTotal += dealCard(deck);
    std::cout << "Dealer drew a " << dealerTotal << ". Dealer total: " << dealerTotal << std::endl;

    dealerTotal += dealCard(deck);
    std::cout << "Dealer total after two cards: " << dealerTotal << std::endl;

    // Dealer draws until their total is 17 or higher
    while (dealerTotal < 17) {
        int nextCard = dealCard(deck);
        dealerTotal += nextCard;
        std::cout << "Dealer drew a " << nextCard << ". Dealer total: " << dealerTotal << std::endl;
    }

    return dealerTotal; // You may want to change this return value 
}

// TODO (4): Complete the following function
void determineWinner(int playerTotal, int dealerTotal) {

    // - If the player has busted (gone over 21), they lose automatically, 
    //   regardless of the dealer's score.
    // - If the dealer has busted, the player wins, unless the player also busted.
    // - If neither player nor dealer busts, the total closest to 21 wins.
    // - If both have the same total, it is a tie.
    // Update the global variables at the top accordingly 
    //player bust
    if (playerTotal > 21) {
        std::cout << "You busted! Dealer wins this round." << std::endl;
        dealerWins++;
    }
    //dealer bust
    else if (dealerTotal > 21) {
        std::cout << "Dealer busted! You win this round." << std::endl;
        playerWins++;
    }
    //player win
    else if (playerTotal > dealerTotal) {
        std::cout << "You win! Your score: " << playerTotal << ", Dealer score: " << dealerTotal << std::endl;
        playerWins++;
    }
    //dealer win
    else if (dealerTotal > playerTotal) {
        std::cout << "Dealer wins! Dealer score: " << dealerTotal << ", Your score: " << playerTotal << std::endl;

        dealerWins++;
    }
    //tie
    else {
        std::cout << "It's a tie! Both scored: " << playerTotal << std::endl;
        ties++;
    }
}

void playGame() {
    // Vector representing the deck with numbers
    std::vector<int> deck = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11,  // First set
                              2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 }; // Second set (simulating two decks)


    // TODO (5): do the main game functionality by calling the previous functions
    // 5.1 Shuffle the deck
    shuffleDeck(deck);
    // 5.2 Make the player play, followed by the dealer
    int playerScore = playerTurn(deck);

    //dealer if player never busted
    int dealerScore = 0;
    if (playerScore <= 21) {
        dealerScore = dealerTurn(deck);
    }
    // 5.3 Determine the winner
    determineWinner(playerScore, dealerScore);
    

    // Prints the game stats
    std::cout << "Stats: Player Wins: " << playerWins << ". Dealer Wins: " << dealerWins << ". Ties: " << ties << std::endl;
    
}