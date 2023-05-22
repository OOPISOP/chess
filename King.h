/***********************************************************************
 * File: King.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: King piece define
***********************************************************************/
#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>

using namespace std;

class King : public Piece//inheritance Piece
{
public:
    King(bool white,int type);
    virtual Piece* clone()const override;//clone the piece

    virtual bool canMove(Board board,Spot start,Spot end) override;//override canMove
    bool isValidCastling(Board board,Spot start,Spot end);//is valid castling

};

#endif // KING_H
