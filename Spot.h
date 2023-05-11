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
    bool mark;
public:
    Spot(int x,int y,Piece* piece);
    Spot(int x,int y);
    Piece* getPiece()const;
    void setPiece(Piece* p);
    void setPiece();
    int getX()const;
    void setX(int x);
    int getY()const;
    void setY(int y);
    bool havePiece();
    void setMark(bool mark);
    bool getMark();
};

#endif // SPOT_H
