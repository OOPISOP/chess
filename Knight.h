#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>

using namespace std;

class Knight : public Piece
{
public:
    Knight(bool white,int type);
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
};

#endif // KNIGHT_H
