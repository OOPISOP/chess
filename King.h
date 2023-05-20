#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"
#include "Spot.h"
#include <iostream>

using namespace std;

class King : public Piece
{
public:
    King(bool white,int type);
    virtual Piece* clone()const override;

    virtual bool canMove(Board board,Spot start,Spot end) override;
    bool isValidCastling(Board board,Spot start,Spot end);

};

#endif // KING_H
