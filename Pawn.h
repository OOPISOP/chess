#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>

using namespace std;

class Pawn : public Piece//inheritance Piece
{
public:
    Pawn(bool white,int type);
    virtual Piece* clone()const override;//clone the piece

    virtual bool canMove(Board board,Spot start,Spot end) override;//override can move
};

#endif // PAWN_H
