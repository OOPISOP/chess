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


void Piece::setWhite(bool white)
{
    this->white = white;
}
void Piece::setType(int type)
{
    this->type = type;
}
void Piece::setMoved(bool moved)
{
    this->moved = moved;
}
void Piece::setChecked(bool checked)
{
    this->checked = checked;
}
void Piece::setPromoting(bool promoting)
{
    this->promoting = promoting;
}
void Piece::setEnPassant(bool enPassant)
{
    this->enPassant = enPassant;
}
void Piece::setCastling(bool castling)
{
    this->castling = castling;
}

bool Piece::getWhite() const
{
    return this->white;
}
int Piece::getType() const
{
    return this->type;
}
bool Piece::getMoved() const
{
    return this->moved;
}
bool Piece::getChecked()const
{
    return this->checked;
}
bool Piece::getPromoting() const
{
    return this->promoting;
}
bool Piece::getEnPassant()const
{
    return this->enPassant;
}
bool Piece::getCastling()const
{
    return this->castling;
}
