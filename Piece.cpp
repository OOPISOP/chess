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

bool Piece::isMoved()
{
    return this->moved;
}
void Piece::setMoved(bool moved)
{
    this->moved = moved;

}

int Piece::getType()
{
    return this->type;
}

void Piece::setType(int type)
{
    this->type = type;
}


void Piece::setPromoting(bool promoting)
{
    this->promoting = promoting;
}
bool Piece::isPromoting()
{
    return this->promoting;
}
void Piece::setEnPassant(bool enPassant)
{
    this->enPassant = enPassant;
}
bool Piece::isEnPassant()
{
    return this->enPassant;
}
void Piece::setCastling(bool castling)
{
    this->castling = castling;
}
bool Piece::isCastling()
{
    return this->castling;
}

