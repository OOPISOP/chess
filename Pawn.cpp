    #include "Pawn.h"

Pawn::Pawn(bool white,int type) : Piece(white,type)
{

}

bool Pawn::canMove(Board board,Spot start,Spot end)
{

    if(end.havePiece() && end.getPiece()->isWhite() == this->isWhite())
    {
        return false;
    }
    int delta = start.getPiece()->isWhite() ? -1 : 1 ;
    if((end.getY()-start.getY()) != delta)
    {
        return false;
    }
    return true;
}
