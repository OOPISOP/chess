#include "Spot.h"

Spot::Spot(int x,int y,Piece* piece) : piece(piece),x(x),y(y)
{
    this->isPiece = true;
    this->mark = false;
}

Spot::Spot(int x,int y) :x(x),y(y)
{
    this->isPiece = false;
    this->mark = false;
}

bool Spot::havePiece()
{
    return this->isPiece;
}

Piece* Spot::getPiece()const
{
    return this->piece;
}
void Spot::setPiece(Piece *p)
{
    this->piece = p;
    this->isPiece = true;
    this->mark = false;
}
void Spot::setPiece()
{
    Piece* p = nullptr;
    this->piece = p;
    this->isPiece = false;
    this->mark = false;
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

void Spot::setMark(bool mark)
{
    this->mark = mark;
}

bool Spot::getMark()
{
    return this->mark;
}
