#include "Pawn.h"

Pawn::Pawn(bool white,int type) : Piece(white,type)
{
}

Piece* Pawn::clone()const
{
    return new Pawn(*this);
}

bool Pawn::canMove(Board board,Spot start,Spot end)
{
    //Cannot out of range
    if(end.getX()>7||end.getX()<0||end.getY()>7||end.getY()<0)
    {
        return false;
    }

    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
    {
        return false;
    }

    // Normally move 1 forward unit.
    int delta = start.getPiece()->getWhite() ? -1 : 1;

    // Cannot move 1 forward unit when the front is blocked.
    if (abs(end.getX() - start.getX()) == 0)
    {
        if (start.getY()+delta>7||start.getY()+delta<0)
        {
            return false;
        }

        Spot frontSpot = board.getBox(start.getY()+delta,start.getX());

        if(frontSpot.havePiece())
        {
            return false;
        }
    }
    // Cannot move 1 diagonal unit when the front is blocked or no enemy.
    else if ((abs(end.getX() - start.getX()) == 1))
    {
        Spot near = board.getBox(start.getY(),start.getX() + (end.getX() - start.getX()));

        if(near.havePiece())
        {
            if(!(end.havePiece())&&near.getPiece()->getEnPassant()&&((end.getY() - start.getY()) == delta))
            {
                cout<<near.getX()<<" "<<near.getY()<<endl;

                return true;
            }
        }

        if (!(end.havePiece())||(((abs(end.getY() - start.getY()) > 1))))
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
    // Only available on row 2 or 7.
    if ((start.getY() == 1) || (start.getY() == 6))
    {
        int delta2 = start.getPiece()->getWhite() ? -2 : 2 ;

        //when 2 forward units cannot have piece
        if((end.getY() - start.getY()) == delta2)
        {
            if(start.getY()+delta2 > 7||start.getY()+delta2 < 0)
            {
                return false;
            }

            Spot frontTwoSpot = board.getBox(start.getY()+delta2,start.getX());

            if(frontTwoSpot.havePiece())
            {
                return false;
            }
        }

        // Cannot move except 1 or 2 forward units.
        if (((end.getY() - start.getY()) != delta) &&
            ((end.getY() - start.getY()) != delta2))
        {
            return false;
        }

        return true;
    }

    // Cannot move except 1 forward unit.
    if((end.getY() - start.getY()) != delta)
    {
        return false;
    }
    return true;
}
