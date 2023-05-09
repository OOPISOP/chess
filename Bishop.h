#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
using namespace std;
class Bishop : public Piece
{
public:
    Bishop(bool white,int type);
    virtual bool canMove(Board board,Spot start,Spot end) override;
};

#endif // BISHOP_H
