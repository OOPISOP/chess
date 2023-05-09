#include "Rook.h"

Rook::Rook(bool white,int type) :Piece(white,type)
{

}
bool Rook::canMove(Board board,Spot start,Spot end)
{
    if(end.getPiece()->isWhite() == this->isWhite())
    {
        return false;
    }
    int delta = start.getPiece()->isWhite() ? -1 : 1 ;
    if(end.getY()-start.getY()!= delta)
    {
        return false;
    }
    return true;
}
