#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
using namespace std;

class Queen : public Piece
{
public:
    Queen(bool white,int type);
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
};

#endif // QUEEN_H
