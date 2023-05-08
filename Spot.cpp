#include "Spot.h"

Spot::Spot(int x,int y,Piece piece) : piece(piece),x(x),y(y)
{
    this->isPiece = true;
}

Spot::Spot(int x,int y) :x(x),y(y)
{
    this->isPiece = false;
}

bool Spot::havePiece()
{
    return this->isPiece;
}

Piece Spot::getPiece()const
{
    return this->piece;
}
void Spot::setPiece(Piece p)
{
    this->piece = p;
}
int Spot::getX()const
{
    return this->x;
}
void Spot::setX(int x)
{
    this->x = x;
}
int Spot::getY()const
{
    return this->y;
}
void Spot::setY(int y)
{
    this->y = y;
}
