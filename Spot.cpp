#include "Spot.h"

Spot::Spot(int x,int y,Piece* piece) : piece(piece),x(x),y(y)
{
    this->isPiece = true;
    this->marked = false;
}

Spot::Spot(int x,int y) :x(x),y(y)
{
    this->isPiece = false;
    this->marked = false;
}

void Spot::setPiece(Piece *p)
{
    this->piece = p;
    this->isPiece = true;
    this->marked = false;
}

void Spot::setPiece()
{
    Piece* p = nullptr;
    this->piece = p;
    this->isPiece = false;
    this->marked = false;
}

void Spot::setX(int x)
{
    this->x = x;
}

void Spot::setY(int y)
{
    this->y = y;
}

void Spot::setMark(bool mark)
{
    this->marked = mark;
}

Piece* Spot::getPiece()const
{
    return this->piece;
}

int Spot::getX()const
{
    return this->x;
}

int Spot::getY()const
{
    return this->y;
}

bool Spot::havePiece()const
{
    return this->isPiece;
}

bool Spot::getMark()
{
    return this->marked;
}
