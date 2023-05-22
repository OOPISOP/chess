/***********************************************************************
 * File: Queen.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Queen piece imp
***********************************************************************/
#include "Queen.h"

Queen::Queen(bool white,int type) : Piece(white,type)
{
}
//Intent:clone
//Pre:Queen
//Pos:return piece point
Piece* Queen::clone()const
{
    return new Queen(*this);
}
//Intent:can move
//Pre:board start end spot
//Pos:return bool
bool Queen::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
    {
        return false;
    }

    // Declaration for informative variables.
    int deltaX = end.getX() - start.getX();
    int deltaY = end.getY() - start.getY();

    // Cannot move except vertically, horizontally or diagonally.
    if (((deltaX != 0) && (deltaY != 0)) && (abs(deltaX) != abs(deltaY)))
    {
        return false;
    }

    // Declaration for informative variables.
    int leftOrRight = (deltaX == 0) ? 0 : ((deltaX > 0) ? 1 : -1);
    int upOrDown = (deltaY == 0) ? 0 : ((deltaY > 0) ? 1 : -1);
    int colX = (start.getX() + leftOrRight), rowY = (start.getY() + upOrDown);

    // Check whether there is any piece on the path to target.
    // Check whether queen move at least one unit.
    while ((colX != end.getX()) || (rowY != end.getY()))
    {
        if (board.getBox(rowY, colX).havePiece())
        {
            return false;
        }

        colX += leftOrRight;
        rowY += upOrDown;
    }

    return true;
}
