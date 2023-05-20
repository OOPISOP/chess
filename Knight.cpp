#include "Knight.h"

Knight::Knight(bool white,int type) : Piece(white,type)
{
}

Piece* Knight::clone()const
{
    return new Knight(*this);
}

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
