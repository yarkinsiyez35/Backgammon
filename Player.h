#include "Board.h"
#include <string>
#include "Dice.h"
#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player(std::string str, char p, bool direction, bool broken, bool r, Board &b, Dice &die1, Dice & die2);         //constructor
    void playGame();
    bool canMove(int &roll1 ,int & roll2);
    void makeMove(int &roll);                //makes the move, returns 1 if the move is successful, 0 else
    void checkConditions();         //checks whether to insert a broken piece, regular move, or removal move
    bool isWinner() const;                //returns true if a player has won
    std::string getName() const;          //returns the name of the player

private:
    std::string name;
    char piece;
    bool clockwise;                 //direction
    bool brokenPiece;               //will be checked and modified every turn
    bool remove;                    //will become true at the end of the game
    Board* board;                   //shared object
    Dice* d1;                       //die 1
    Dice* d2;                       //die 2
};


#endif //PLAYER_H
