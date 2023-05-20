#include "Spot.h"

Spot::Spot(int x,int y,Piece* piece) : piece(piece),x(x),y(y)
{
    this->isPiece = true;
<<<<<<< HEAD
    this->mark = false;
=======
    this->marked = false;
>>>>>>> 512f4a0 (f)
}

Spot::Spot(int x,int y) :x(x),y(y)
{
    this->isPiece = false;
<<<<<<< HEAD
    this->mark = false;
}

bool Spot::havePiece()const
{
    return this->isPiece;
}

Piece* Spot::getPiece()const
{
    return this->piece;
}
=======
    this->marked = false;
}

>>>>>>> 512f4a0 (f)
void Spot::setPiece(Piece *p)
{
    this->piece = p;
    this->isPiece = true;
<<<<<<< HEAD
    this->mark = false;
}
=======
    this->marked = false;
}

>>>>>>> 512f4a0 (f)
void Spot::setPiece()
{
    Piece* p = nullptr;
    this->piece = p;
    this->isPiece = false;
<<<<<<< HEAD
    this->mark = false;
}

int Spot::getX()const
{
    return this->x;
}
=======
    this->marked = false;
}

>>>>>>> 512f4a0 (f)
void Spot::setX(int x)
{
    this->x = x;
}
<<<<<<< HEAD
int Spot::getY()const
{
    return this->y;
}
=======

>>>>>>> 512f4a0 (f)
void Spot::setY(int y)
{
    this->y = y;
}

void Spot::setMark(bool mark)
{
<<<<<<< HEAD
    this->mark = mark;
=======
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
>>>>>>> 512f4a0 (f)
}

bool Spot::getMark()
{
<<<<<<< HEAD
    return this->mark;
=======
    return this->marked;
>>>>>>> 512f4a0 (f)
}
