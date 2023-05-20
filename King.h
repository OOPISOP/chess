#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
<<<<<<< HEAD
using namespace std;
=======

using namespace std;

>>>>>>> 512f4a0 (f)
class King : public Piece
{
public:
    King(bool white,int type);
<<<<<<< HEAD
    virtual bool canMove(Board board,Spot start,Spot end);
    virtual Piece* clone()const override;
    bool isValidCastling(Board board,Spot start,Spot end);
    bool seeCheck(Board board,bool white,Spot enemyKingsSpot);
=======
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
    bool isValidCastling(Board board,Spot start,Spot end);

>>>>>>> 512f4a0 (f)
};

#endif // KING_H
