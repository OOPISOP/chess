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

bool Piece::isWhite() const
{
    return this->white;
}
void Piece::setWhite(bool white)
{
    this->white = white;
}

bool Piece::isMoved() const
{
    return this->moved;
}
void Piece::setMoved(bool moved)
{
    this->moved = moved;

}

int Piece::getType() const
{
    return this->type;
}

void Piece::setType(int type)
{
    this->type = type;
}

bool Piece::isChecked()const
{
    return this->checked;

}
void Piece::setChecked(bool checked)
{
    this->checked = checked;
}

void Piece::setPromoting(bool promoting)
{
    this->promoting = promoting;
}
bool Piece::isPromoting() const
{
    return this->promoting;
}
void Piece::setEnPassant(bool enPassant)
{
    this->enPassant = enPassant;
}
bool Piece::isEnPassant()const
{
    return this->enPassant;
}
void Piece::setCastling(bool castling)
{
    this->castling = castling;
}
bool Piece::isCastling()const
{
    return this->castling;
}

