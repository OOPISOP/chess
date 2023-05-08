#ifndef SPOT_H
#define SPOT_H

#include "Piece.h"

class Spot
{
private:
    Piece piece;
    int x;
    int y;
public:
    Spot(int x,int y,Piece piece);
    Piece getPiece()const;
    void setPiece(Piece p);
    int getX()const;
    void setX(int x);
    int getY()const;
    void setY(int y);
};

#endif // SPOT_H
