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
    virtual bool canMove(Board board,Spot start,Spot end);
    virtual Piece* clone()const override;
};

#endif // QUEEN_H
