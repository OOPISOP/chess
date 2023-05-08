#include "Piece.h"

Piece::Piece(bool white,int type)
{
    this->setWhite(white);
    this->setType(type);
}

Piece::Piece()
{
    this->setWhite(true);
    this->setType(6);
}

bool Piece::isWhite()
{
    return this->white;
}
void Piece::setWhite(bool white)
{
    this->white = white;
}
bool Piece::isKilled()
{
    return this->killed;
}
void Piece::setKilled(bool killed)
{
    this->killed = killed;
}

int Piece::getType()
{
    return this->type;
}

void Piece::setType(int type)
{
    this->type = type;
}
