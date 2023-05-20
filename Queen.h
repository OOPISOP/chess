#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>
<<<<<<< HEAD
using namespace std;
=======

using namespace std;

>>>>>>> 512f4a0 (f)
class Queen : public Piece
{
public:
    Queen(bool white,int type);
<<<<<<< HEAD
    virtual bool canMove(Board board,Spot start,Spot end);
    virtual Piece* clone()const override;
=======
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
>>>>>>> 512f4a0 (f)
};

#endif // QUEEN_H
