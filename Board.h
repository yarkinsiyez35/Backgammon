#include "Stack.h"

#ifndef TAVLA_BOARD_H
#define TAVLA_BOARD_H


class Board {
public:
    Board(char piece1 = 'O', char piece2 = 'X');                                                            //constructor

    /*for piece traversal*/
    bool possibleNormalMove(bool direction, char piece, int dice) const;                            //checks for any possible move for the player
    bool validMove(bool direction, char piece, int dice, int startingIndex) const;           //checks if the user's input is valid
    void makeNormalMove(bool direction, char piece, int dice, int startingIndex);         //makes the move for the player from that index

    /*for adding the broken pieces to the game*/
    void breakPiece(bool direction, int index);                                        //breaks the piece in that index and moves it to the respective broken piece stack, direction is of the broken piece
    bool possibleBrokenMove(bool direction, char piece, int dice) const;             //checks if there is a way to add the broken piece to the game
    void makeBrokenMove(bool direction, char piece, int die);                       //adds the broken piece to the desired stack
    int sizeOfStack(int index) const;                                                                 //returns the size of one stack
    void Print() const;                           //prints the board

    /*for removing the pieces at the final of the game*/
    bool canRemove(bool direction, char piece) const;                                                     //checks if a player can start removing
    bool possibleRemovalMove(bool direction, char piece, int dice) const;                            //checks for any possible removal move for the player
    bool validRemovalMove(bool direction, char piece, int dice, int startingIndex) const;            //checks if the user's input is valid
    void makeRemovalMove(bool direction, int startingIndex);                   //removes the piece from the desired stack s

    /*winning condition*/
    bool checkPiece(char piece) const;                                                                    //checks if that piece exists anywhere on the board
    

private:
    Stack * array;                  //24 stacks for the actual board, 2 more for the broken pieces
};


#endif //TAVLA_BOARD_H
