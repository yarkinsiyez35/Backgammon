#include "Player.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

std::string toString(const int & roll1, const int& roll2)
{
    std::string temp;
    std::stringstream stream1;
    stream1 << roll1;
    stream1 >> temp;
    stream1.clear();
    stream1 << roll2;
    std::string temp2;
    stream1 >> temp2;
    temp += " & ";
    temp += temp2;
    return temp;
}

Player::Player(std::string str,char p, bool direction, bool broken, bool r, Board &b, Dice &die1, Dice & die2) : board(&b), d1(&die1), d2(&die2)
{
    name = str;
    piece = p;
    clockwise = direction;
    brokenPiece = broken;
    remove = r;
}


void Player::playGame()
{
    std::cout << name << ", two dice are thrown. Your dies are: ";
    int roll1 = d1->Roll();
    int roll2 = d1->Roll();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << roll1 << " & " << roll2 << std::endl;
    std::string diceString = toString(roll1, roll2);


    //displays the board

    while (canMove(roll1, roll2))            //will stop executing when there are not any possible moves
    {
        std::cout << "This is the current board:\n\n";
        board->Print();

        std::cout << "Your dies: " << diceString << std::endl;
        std::cout << "Which die would you like to play with first: Input '1' for the first, '2' for the second die: ";
        int input;
        std::cin >> input;
        if (input == 1)                                             //first die
        {
            if(roll1 >0)                                            //if that die is not used yet
            {
                makeMove(roll1);                                //will update the die if move is successful
            }
            else                                                    //stops the die from being used again
            {
                std::cout << "You have already made a move with that die.\n";
            }
        }
        else                                                        //second die
        {
            if (roll2 >0)                                           //if that die is not used yet
            {
                makeMove(roll2);                                //will update the die if move is successful
            }
            else                                                    //stops the die from being used again
            {
                std::cout << "You have already made a move with that die.\n";
            }
        }
    }
    std::cout << "Your turn is over.\n";

}


bool Player::canMove(int &roll1, int &roll2)
{
    if (roll1 == -1 && roll2 == -1)             //if both dies are used
    {
        return false;
    }
    checkConditions();
    if (brokenPiece)
    {
        if(roll1>0)
        {
            if (board->possibleBrokenMove(clockwise,piece, roll1))              //if there is a move with the first die
            {
                return true;
            }
        }
        if (roll2 > 0)
        {
            if (board->possibleBrokenMove(clockwise, piece, roll2))
            {
                return true;                                                        //if there is a move with the second die
            }
        }
        return false;                   //returns false since there is not a possible move
    }
    if (remove)
    {
        if (roll1>0)
        {
            if (board->possibleRemovalMove(clockwise,piece,roll1)|| board->possibleNormalMove(clockwise,piece,roll1))       //if a player can remove or move the piece
            {
                return true;
            }
        }
        if (roll2>0)
        {
            if (board->possibleRemovalMove(clockwise,piece,roll2)|| board->possibleNormalMove(clockwise,piece,roll2))       //if a player can remove or move the piece
            {
                return true;
            }
        }
        return false;                           //returns false since there is not a possible move
    }
    if (roll1>0)
    {
        if (board->possibleNormalMove(clockwise,piece, roll1))                      //if there is a normal move
        {
            return true;
        }
    }
    if(roll2>0)
    {
        if (board->possibleNormalMove(clockwise,piece,roll2))               //if there is a normal move
        {
            return true;
        }
    }
    return false;
}


void Player::makeMove(int &roll1)
{
    if (brokenPiece)                //player will insert a broken piece
    {
        if (board->possibleBrokenMove(clockwise,piece,roll1))           //if there is a possible move
        {
            board->makeBrokenMove(clockwise,piece,roll1);           //makes the move
            roll1 = -1;                                                          //updates the die
            return;
        }
        std::cout << "You cannot insert a piece with that die\n";
        return;
    }
    else                            //player does not have a broken piece
    {
        if (remove)                     //player will try to remove a piece
        {
            if (board->possibleRemovalMove(clockwise,piece,roll1))
            {
                board->makeRemovalMove(clockwise,roll1);
                roll1 = -1;
                return;
            }
            std::cout << "You cannot remove a piece with that die.\n";
        }
        //make normal move
        if(board->possibleNormalMove(clockwise,piece,roll1))            //if there is a possible normal move with that die
        {
            bool condition = true;
            while (condition)
            {
                std::cout << "You have a possible move with the die, choose your starting index to make the move: ";
                int index;
                std::cin >> index;
                if (board->validMove(clockwise,piece,roll1, index))             //if player's move is valid
                {
                    board->makeNormalMove(clockwise,piece,roll1,index);     //makes the move
                    condition = false;                                                               //updates the condition
                    roll1 = -1;                                                                      //updates the die
                }
            }
        }
        else                                                                        //if there is not a possible normal move with that die
        {
            std::cout << "You cannot make a normal move with that die.\n";
        }
    }
}



void Player::checkConditions()
{

    if (clockwise)
    {
        /*checks for broken pieces*/
        brokenPiece = (board->sizeOfStack(24) != 0);
        remove = board->canRemove(clockwise, piece) && !brokenPiece;            //returns if player can start removing pieces
    }
    else
    {
        /*checks for broken pieces*/
        brokenPiece = (board->sizeOfStack(25) != 0);
        remove = board->canRemove(clockwise, piece) && !brokenPiece;            //returns if player can start removing pieces
    }
}


bool Player::isWinner() const
{
    return board->checkPiece(piece);
}

std::string Player::getName() const
{
    return name;
}
