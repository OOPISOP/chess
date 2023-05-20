#include "Knight.h"

Knight::Knight(bool white,int type) : Piece(white,type)
{
<<<<<<< HEAD

}
bool Knight::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->isWhite() == this->isWhite())
=======
}

Piece* Knight::clone()const
{
    return new Knight(*this);
}

bool Knight::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
>>>>>>> 512f4a0 (f)
    {
        return false;
    }

    // Declaration for informative variables.
    int deltaX = end.getX() - start.getX();
    int deltaY = end.getY() - start.getY();
<<<<<<< HEAD
    // Can have L-shaped move.
    return (((abs(deltaX) == 1) && (abs(deltaY) == 2)) || ((abs(deltaX) == 2) && (abs(deltaY) == 1)));
}

Piece* Knight::clone()const
{
    return new Knight(*this);
}
=======

    // Can have L-shaped move.
    return (((abs(deltaX) == 1) && (abs(deltaY) == 2)) || ((abs(deltaX) == 2) && (abs(deltaY) == 1)));
}
>>>>>>> 512f4a0 (f)
