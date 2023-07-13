#include <iostream>
#include "Dice.h"
#include "Board.h"
#include "Player.h"

int main() {

    std::cout << "Welcome to Tavla, created by Yarkın Siyez.\n";
    std::cout << "What will be the name of the first player: ";
    std::string p1Name,p2Name;
    std::cin >> p1Name;
    std::cout << p1Name << ", pick your piece: ";
    char p1piece, p2piece;
    std::cin >> p1piece;
    std::cout << "What will be the name of the second player: ";
    std::cin >> p2Name;
    std::cout << p2Name << ", pick your piece: ";
    std::cin >> p2piece;
    Dice d1,d2;             //initializes the dice
    Board board(p1piece,p2piece);           //initializes the board


    Player p1(p1Name,p1piece,false,false,false,board,d1,d2);         //initializes the player
    Player p2(p2Name,p2piece,true,false,false,board,d1,d2);         // initializes the player

    while(p1.isWinner() && p2.isWinner())         //while there is not a winner
    {
        p1.playGame();
        p2.playGame();
    }

    if (p1.isWinner())
    {
        if (p2.isWinner())
        {
            std::cout << "Friendship wins!\n";
        }
        else
        {
            std::cout << p1.getName() << " wins!\n";
        }
    }
    else
    {
        std::cout << p2.getName() << " wins!\n";
    }

    std::cout << "Thank you for playing Tavla, created by Yarkın Siyez\n";

    return 0;
}
