#include "Pawn.h"

Pawn::Pawn(bool white,int type) : Piece(white,type)
{

}

bool Pawn::canMove(Board board,Spot start,Spot end)
{
    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->isWhite() == this->isWhite())
    {
        return false;
    }


    // Normally move 1 forward unit.
    int delta = start.getPiece()->isWhite() ? -1 : 1 ;

    Spot frontSpot = board.getBox(start.getY()+delta,start.getX());

    // Cannot move 1 forward unit when the front is blocked.
    if (abs(end.getX() - start.getX()) == 0)
    {
        if (frontSpot.havePiece())
        {
            return false;
        }
    }
    // Cannot move 1 diagonal unit when the front is blocked or no enemy.
    else if ((abs(end.getX() - start.getX()) == 1))
    {
        if (!(end.havePiece()))
        {
            return false;
        }
    }
    // Cannot move exceptinally from above condition.
    else
    {

        return false;
    }

    // First move can forward 2 units.
    if (!isMoved())
    {
        // Only available on row 2 or 7.
        if ((start.getY() == 1) || (start.getY() == 6))
        {
            int delta2 = start.getPiece()->isWhite() ? -2 : 2 ;

            // Cannot move except 1 or 2 forward units.
            if (((end.getY() - start.getY()) != delta) &&
                ((end.getY() - start.getY()) != delta2))
            {
                return false;
            }

            setMoved(true);
            return true;
        }
    }

    // Cannot move except 1 forward unit.
    if((end.getY() - start.getY()) != delta)
    {
        return false;
    }

    // Check promotion.
    if ((start.getY() == 1) || (start.getY() == 6))
    {
        setPromoting(true);
    }

    setMoved(true);
    return true;
}
