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

<<<<<<< HEAD
bool Piece::isWhite() const
{
    return this->white;
}
=======
>>>>>>> 512f4a0 (f)
void Piece::setWhite(bool white)
{
    this->white = white;
}
<<<<<<< HEAD

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

=======
>>>>>>> 512f4a0 (f)
void Piece::setType(int type)
{
    this->type = type;
}
<<<<<<< HEAD

bool Piece::isChecked()const
{
    return this->checked;

=======
void Piece::setMoved(bool moved)
{
    this->moved = moved;
>>>>>>> 512f4a0 (f)
}
void Piece::setChecked(bool checked)
{
    this->checked = checked;
}
<<<<<<< HEAD

=======
>>>>>>> 512f4a0 (f)
void Piece::setPromoting(bool promoting)
{
    this->promoting = promoting;
}
<<<<<<< HEAD
bool Piece::isPromoting() const
{
    return this->promoting;
}
=======
>>>>>>> 512f4a0 (f)
void Piece::setEnPassant(bool enPassant)
{
    this->enPassant = enPassant;
}
<<<<<<< HEAD
bool Piece::isEnPassant()const
{
    return this->enPassant;
}
=======
>>>>>>> 512f4a0 (f)
void Piece::setCastling(bool castling)
{
    this->castling = castling;
}
<<<<<<< HEAD
bool Piece::isCastling()const
{
    return this->castling;
}

=======

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
>>>>>>> 512f4a0 (f)
