/***********************************************************************
 * File: Queen.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Queen class define
***********************************************************************/
#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
using namespace std;

class Queen : public Piece//inheritance Piece
{
public:
    Queen(bool white,int type);
    virtual Piece* clone()const override;//clone the piece

    virtual bool canMove(Board board,Spot start,Spot end) override;//override can move
};

#endif // QUEEN_H
