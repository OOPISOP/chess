#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
using namespace std;

class Rook : public Piece
{
public:
    Rook(bool white,int type);
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
};

#endif // ROOK_H
