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
    virtual bool canMove(Board board,Spot start,Spot end);
    bool isValidCastling(Board board,Spot start,Spot end);
    bool seeCheck(Board board,bool white,Spot enemyKingsSpot);
};

#endif // KING_H
