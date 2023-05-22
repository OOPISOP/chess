/***********************************************************************
 * File: Bishop.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Bisghop piece define
***********************************************************************/
#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>

using namespace std;

class Bishop : public Piece//inheritance Piece
{
public:
    Bishop(bool white,int type);
    virtual Piece *clone()const override;//clone the Piece

    virtual bool canMove(Board board,Spot start,Spot end) override;//override canMove
};

#endif // BISHOP_H
