#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
using namespace std;

class Pawn : public Piece
{
public:
    Pawn(bool white,int type);
    virtual bool canMove(Board board,Spot start,Spot end);
    virtual Piece* clone()const override;
};

#endif // PAWN_H
