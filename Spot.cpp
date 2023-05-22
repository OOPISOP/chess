/***********************************************************************
 * File: Spot.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Spot imp
***********************************************************************/
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
//Intent:set piece
//Pre:piece pointer
//Pos:set piece
void Spot::setPiece(Piece *p)
{
    this->piece = p;
    this->isPiece = true;
    this->marked = false;
}
//Intent:set piece
//Pre:piece pointer
//Pos:set piece
void Spot::setPiece()
{
    Piece* p = nullptr;
    this->piece = p;
    this->isPiece = false;
    this->marked = false;
}
//Intent:set x
//Pre:x
//Post:set x
void Spot::setX(int x)
{
    this->x = x;
}
//Intent:set y
//Pre:y
//Post:set y
void Spot::setY(int y)
{
    this->y = y;
}
//Intent:setMark
//Pre:makr
//Post:setMark
void Spot::setMark(bool mark)
{
    this->marked = mark;
}
//Intent:getPiece
//Pre:piece
//Post:getPiece
Piece* Spot::getPiece()const
{
    return this->piece;
}
//Intent:get x
//Pre:x
//Post:get x
int Spot::getX()const
{
    return this->x;
}
//Intent:get y
//Pre:y
//Post:get y
int Spot::getY()const
{
    return this->y;
}
//Intent:have piece
//Pre:piece
//Post:return bool
bool Spot::havePiece()const
{
    return this->isPiece;
}
//Intent:getMark
//Pre:mark
//Post:return bool
bool Spot::getMark()
{
    return this->marked;
}
