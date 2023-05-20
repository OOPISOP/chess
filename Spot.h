#ifndef SPOT_H
#define SPOT_H

#include "Piece.h"

class Spot
{
private:
    Piece* piece;
    int x;
    int y;
    bool isPiece;
    bool marked;

public:
    Spot(int x,int y,Piece* piece);
    Spot(int x,int y);

    void setPiece(Piece* p);
    void setPiece();
    void setX(int x);
    void setY(int y);
    void setMark(bool mark);

    Piece* getPiece()const;
    int getX()const;
    int getY()const;
    bool havePiece()const;
    bool getMark();
};

#endif // SPOT_H
