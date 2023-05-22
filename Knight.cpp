/***********************************************************************
 * File: Kngiht.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: King piece imp
***********************************************************************/
#include "Knight.h"

Knight::Knight(bool white,int type) : Piece(white,type)
{
}
//Intent:clone
//Pre:kngiht
//Pos:return piece point
Piece* Knight::clone()const
{
    return new Knight(*this);
}
//Intent:can move
//Pre:board start end spot
//Pos:return bool
bool Knight::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
    {
        return false;
    }

    // Declaration for informative variables.
    int deltaX = end.getX() - start.getX();
    int deltaY = end.getY() - start.getY();

    // Can have L-shaped move.
    return (((abs(deltaX) == 1) && (abs(deltaY) == 2)) || ((abs(deltaX) == 2) && (abs(deltaY) == 1)));
}
