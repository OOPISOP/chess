#include "Rook.h"

Rook::Rook(bool white,int type) :Piece(white,type)
{
}

Piece* Rook::clone()const
{
    return new Rook(*this);
}

bool Rook::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
    {
        return false;
    }

    // Declaration for informative variables.
    int deltaX = end.getX() - start.getX();
    int deltaY = end.getY() - start.getY();

    // Cannot move except vertically or horizontally.
    if ((deltaX != 0) && (deltaY != 0))
    {
        return false;
    }

    // Declaration for informative variables.
    int leftOrRight = (deltaX == 0) ? 0 : ((deltaX > 0) ? 1 : -1);
    int upOrDown = (deltaY == 0) ? 0 : ((deltaY > 0) ? 1 : -1);
    int colX = (start.getX() + leftOrRight), rowY = (start.getY() + upOrDown);

    // Check whether there is any piece on the path to target.
    // Check whether rook move at least one unit.
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
