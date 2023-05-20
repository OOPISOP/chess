#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
<<<<<<< HEAD
=======

>>>>>>> 512f4a0 (f)
using namespace std;

class Pawn : public Piece
{
public:
    Pawn(bool white,int type);
<<<<<<< HEAD
    virtual bool canMove(Board board,Spot start,Spot end);
    virtual Piece* clone()const override;
=======
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
>>>>>>> 512f4a0 (f)
};

#endif // PAWN_H
