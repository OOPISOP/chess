/***********************************************************************
 * File: Piece.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Piece imp
***********************************************************************/
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

//Intent:set white
//Pre:white
//Pos:set white
void Piece::setWhite(bool white)
{
    this->white = white;
}
//Inent:set type
//Pre:type
//Pos:set type
void Piece::setType(int type)
{
    this->type = type;
}
//Intent:set move
//Pre:move
//Pos:move
void Piece::setMoved(bool moved)
{
    this->moved = moved;
}
//Intent:set check
//Pre:check
//Pos:set check
void Piece::setChecked(bool checked)
{
    this->checked = checked;
}
//Intent:set promot
//Pre:promoting
//Pos:set promot
void Piece::setPromoting(bool promoting)
{
    this->promoting = promoting;
}
//Intent:set en passant
//Pre:en passant
//Pos:set en passant
void Piece::setEnPassant(bool enPassant)
{
    this->enPassant = enPassant;
}
//Intent: set castling
//Pre:castling
//Pos:se castling
void Piece::setCastling(bool castling)
{
    this->castling = castling;
}
//Intent:get white
//Pre:white
//Pos:return bool
bool Piece::getWhite() const
{
    return this->white;
}
//Intent:get type
//Pre:type
//Pos:return type
int Piece::getType() const
{
    return this->type;
}
//Intent:get move
//Pre:move
//Pos:return bool
bool Piece::getMoved() const
{
    return this->moved;
}
//Intent:get check
//Pre:check
//Pos:return bool
bool Piece::getChecked()const
{
    return this->checked;
}
//Intent:get promot
//Pre:promot
//Pos:return ool
bool Piece::getPromoting() const
{
    return this->promoting;
}

//Intent:get en passant
//Pre:en passant
//return bool
bool Piece::getEnPassant()const
{
    return this->enPassant;
}
//Intent:get castling
//Pre:castling
//Pos:return bool
bool Piece::getCastling()const
{
    return this->castling;
}
