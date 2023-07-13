#include "Board.h"
#include <iostream>

Board::Board(char piece1, char piece2)              //constructor 
{
    array = new Stack[26];
    for(int i =0; i< 5; i++)
    {
        array[5].Push(piece1);
        array[12].Push(piece1);
        array[11].Push(piece2);
        array[18].Push(piece2);
    }
    for(int i =0; i< 2 ; i++)
    {
        array[0].Push(piece2);
        array[23].Push(piece1);
    }
    for (int i =0;i<3; i++)
    {
        array[7].Push(piece1);
        array[16].Push(piece2);
    }
}
bool Board::possibleNormalMove(bool direction, char piece, int dice) const
{
    if (direction)          //if the direction is clockwise
    {
        int lastIndex = 24- dice;               //this determines the last index a piece can be moved without leaving the board
        for (int i = 0; i< lastIndex; i++)
        {
            if (array[i].getContent() == piece)            //if it is a stack where the player piece is located
            {
                if (array[i+dice].getContent() == piece || array[i+dice].getSize() < 2)                 //if the destined stack belongs to the player or has size 1 or 0 which means opponent piece can be broken
                {
                    return true;
                }
            }
        }
        return false;                                                   //returns false if there is not any position
    }
    else                    //if the direction is counterclockwise
    {
        int lastIndex = dice-1;                   //this determines the last index a piece can be moved without leaving the board
        for (int i = 23; i> lastIndex; i--)
        {
            if (array[i].getContent() == piece)
            {
                if (array[i-dice].getContent() == piece || array[i-dice].getSize() < 2)               //if the destined stack belongs to the player or has size 1 or 0 which means opponent piece can be broken
                {
                    return true;
                }
            }
        }
        return false;
    }
}


bool Board::validMove(bool direction, char piece, int dice, int startingIndex) const
{
    if (direction)                  //if the direction is clockwise
    {                                       //startingIndex should belong to player and destined stack should belong to the player or should be of size 0 or 1
        if(startingIndex <0 || startingIndex > 23 || startingIndex + dice <0 || startingIndex + dice > 23)                      //index check
        {
            return false;
        }
        return (array[startingIndex].getContent() == piece && (array[startingIndex + dice].getContent() == piece || array[startingIndex+dice].getSize() < 2));
    }
    else                            //if the direction is counterclockwise
    {                                       //startingIndex should belong to player and destined stack should belong to the player or should be of size 0 or 1
        if(startingIndex <0 || startingIndex > 23 || startingIndex -dice <0 || startingIndex -dice > 23)                //index check
        {
            return false;
        }
        return (array[startingIndex].getContent() == piece && (array[startingIndex - dice].getContent() == piece || array[startingIndex-dice].getSize() < 2));
    }
}

void Board::makeNormalMove(bool direction, char piece, int dice, int startingIndex)
{
    if(direction)               //if the direction is clockwise
    {
        array[startingIndex].Pop();                //removes the piece from the starting index

        if(array[startingIndex+dice].getContent() != piece && array[startingIndex+dice].getContent() != ' ')          //if the destined stack belongs to the player
        {
            breakPiece(!direction, startingIndex+dice);              //breaks opponents piece
        }
        array[startingIndex+dice].Push(piece);             //adds the piece to the desired stack
    }
    else                        //if the direction is counterclockwise
    {
        array[startingIndex].Pop();                //removes the piece from the starting index
        if(array[startingIndex-dice].getContent() != piece && array[startingIndex-dice].getContent() != ' ')          //if the destined stack belongs to the player
        {
            breakPiece(!direction, startingIndex-dice);              //breaks opponents piece
        }
        array[startingIndex-dice].Push(piece);             //adds the piece to the desired stack
    }
}


void Board::breakPiece(bool direction, int index)
{
    char piece = array[index].getContent();            //finds the to be broken piece
    array[index].Pop();                    //removes that piece
    if(direction)                   //if the broken piece belongs to the player that goes clockwise
    {
        array[24].Push(piece);         //adds the piece to the broken piece stack
    }
    else                            //if the broken piece belongs to the player that goes counterclockwise
    {
        array[25].Push(piece);     //adds the piece to the broken piece stack
    }
}

bool Board::possibleBrokenMove(bool direction, char piece, int dice) const
{
    if(direction)               //if the direction is clockwise
    {
        return (array[dice].getContent() == piece || array[dice].getSize()<2);                //same logic with previous functions
    }
    else                    //if the direction is counterclockwise
    {
        return (array[24-dice].getContent() == piece || array[24-dice].getSize()<2);              //same logic with previous functions
    }
}


void Board::makeBrokenMove(bool direction, char piece, int die)
{
    if (direction)          //if the direction is clockwise
    {
        array[24].Pop();           //pops the piece from the broken stack
        if (array[die].getContent() != piece && array[die].getContent() != ' ')           //if the stack has opponents piece
        {
            breakPiece(!direction,24-die);           //breaks the piece of the opponent
        }
        array[die].Push(piece);                          //pushes the players piece
    }
    else                    //if the direction is counterclockwise
    {
        array[25].Pop();           //pops the piece from the broken stack
        if (array[24-die].getContent() != piece && array[24-die].getContent() != ' ')           //if the stack has opponents piece
        {
            breakPiece(!direction,die);           //breaks the piece of the opponent
        }
        array[24-die].Push(piece);                          //pushes the players piece
    }
}

int Board::sizeOfStack(int index) const
{
    return array[index].getSize();
}


void Board::Print() const
{

    /*index printing for the columns*/
    for (int i =0; i< 6; i++)
    {
        std::cout << i << "\t";
    }
    std::cout << "||\t";
    for (int i =6; i< 12; i++)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;             //ends the first row

    /*Separator for index and board*/
    for (unsigned short int i = 0; i< 50; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    /*Next 12 rows*/
    for (unsigned short int i = 0; i< 12; i++)         //the next 12 rows for columns 0-11
    {
        for (unsigned short int j = 0; j < 6; j++)               //this loop is for the first 6 columns
        {
            if (array[j].getSize() > i)              //if there is a piece in the ith row, jth column
            {
                std::cout << array[j].getContent() << "\t";
            } else {
                std::cout << " \t";                 //empty string if there is not a piece in the ith row, jth column
            }
        }
        std::cout << "||\t";                                    //separator between columns 5-6
        for (unsigned short int j = 6; j < 12; j++)               //this loop is for the second 6 columns
        {
            if (array[j].getSize() > i)              //if there is a piece in the ith row, jth column
            {
                std::cout << array[j].getContent() << "\t";
            } else {
                std::cout << " \t";                 //empty string if there is not a piece in the ith row, jth column
            }
        }
        std::cout << std::endl;
    }

    /*Boundary setter for the columns between 0-11 and 12-23*/
    for (unsigned short int i = 0; i< 24; i++)
    {
        std::cout << "-";
    }
    std::cout << "||";
    for (unsigned short int i = 0; i< 24; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    /*Next 12 rows*/
    for (short int i = 11; i>-1; i--)         //the next 12 rows for columns 12-23
    {
        for (unsigned short int j = 23; j > 17; j--)               //this loop is for the first 6 columns
        {
            if (array[j].getSize() > i)              //if there is a piece in the ith row, jth column
            {
                std::cout << array[j].getContent() << "\t";
            } else {
                std::cout << " \t";                 //empty string if there is not a piece in the ith row, jth column
            }
        }
        std::cout << "||\t";                    //separator between columns 17-18
        for (unsigned short int j = 17; j > 11; j--)               //this loop is for the second 6 columns
        {
            if (array[j].getSize() > i)              //if there is a piece in the ith row, jth column
            {
                std::cout << array[j].getContent() << "\t";
            } else {
                std::cout << " \t";                 //empty string if there is not a piece in the ith row, jth column
            }
        }
        std::cout << std::endl;
    }



    /*Separator for index and board*/
    for (unsigned short int i = 0; i< 50; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;



    /*index printing for the columns*/
    for (unsigned short int i =23; i> 17; i--)
    {
        std::cout << i << "\t";
    }
    std::cout << "||\t";                    //separator between columns 17-18
    for (int i =17; i> 11; i--)
    {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    std::cout << "Broken Piece clockwise: ";
    for (int i =0; i< array[24].getSize(); i++)
    {
        std::cout << array[24].getContent();
    }

    std::cout << std::endl << "Broken Piece counterclockwise: ";
    for (int i =0; i< array[25].getSize(); i++)
    {
        std::cout << array[25].getContent();
    }


    std::cout << std::endl << std::endl;
}


bool Board::canRemove(bool direction, char piece) const
{
    if(direction)           //if direction is clockwise
    {
        for (unsigned int i =0; i< 18; i++)
        {
            if (array[i].getContent() == piece)                 //if there is a piece that is not in the removal zone
            {
                return false;
            }
        }
        return true;
    }
    else                    //if the direction is counterclockwise
    {
        for (unsigned int i =23; i>5; i--)
        {
            if (array[i].getContent() == piece)                         //if there is a piece that is not in the removal zone
            {
                return false;
            }
        }
        return true;
    }
}

bool Board::possibleRemovalMove(bool direction, char piece, int dice) const
{
    if(direction)           //if the direction is clockwise
    {
        if (array[24-dice].getContent() == piece)               //if a piece is on the actual stack
        {
            return true;
        }
        for (int i = 23-dice; i>17; i--)                        //if the higher ranking stacks have that piece, player cannot remove with that dice
        {
            if (array[i].getContent() == piece)
            {
                return false;
            }
        }
        return true;                                        //returns true if the higher ranking stacks do not contain player's pieces
    }
    else                    //if the direction is counterclockwise
    {
        if (array[dice].getContent() == piece)               //if a piece is on the actual stack
        {
            return true;
        }
        for (int i = dice+1; i<6; i++)                        //if the higher ranking stacks have that piece, player cannot remove with that dice
        {
            if (array[i].getContent() == piece)
            {
                return false;
            }
        }
        return true;                                        //returns true if the higher ranking stacks do not contain player's pieces
    }
}

bool Board::validRemovalMove(bool direction, char piece, int dice, int startingIndex) const         //NOT FINISHED
{
    if (direction)          //if the direction is clockwise
    {
        if(startingIndex > 23 || startingIndex < 18)            //if index is out of bounds
        {
            return false;
        }
        if (array[startingIndex].getContent() == piece)         //if there is a piece on that index
        {
            return true;
        }
        for (int i = 23-dice; i>17; i--)                        //if the higher ranking stacks have that piece, player cannot remove with that dice
        {
            if (array[i].getContent() == piece)
            {
                return false;
            }
        }
        return true;
    }
    else                    //if the direction is counterclockwise
    {
        if(startingIndex > 5 || startingIndex < 0)            //if index is out of bounds
        {
            return false;
        }
        if (array[startingIndex].getContent() == piece)         //if there is a piece on that index
        {
            return true;
        }
        for (int i = dice; i<6; i++)                        //if the higher ranking stacks have that piece, player cannot remove with that dice
        {
            if (array[i].getContent() == piece)
            {
                return false;
            }
        }
        return true;
    }
}


void Board::makeRemovalMove(bool direction, int startingIndex)
{
    if (direction)                          //if the direction is clockwise
    {
        for (int i = startingIndex; i<24; i++)
        {
            if (array[i].getSize() != 0)
            {
                array[i].Pop();                     //pops the first stack that has a piece
                return;                             //stops it from popping more
            }
        }
    }
    else                                    //if the direction is clockwise
    {
        for (int i = startingIndex; i>-1; i--)
        {
            if (array[i].getSize() != 0)
            {
                array[i].Pop();                             //pops the first stack that has a piece
                return;                             //stops it from popping more
            }
        }
    }
}

bool Board::checkPiece(char piece) const            //checks if that piece exists anywhere on the board
{
    for (int i =0; i< 26; i++)
    {
        if (array[i].getContent() == piece)
        {
            return true;
        }
    }
    return false;                           //means player has won
}
