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
<<<<<<< HEAD
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
    bool havePiece()const;
    void setMark(bool mark);
=======
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
>>>>>>> 512f4a0 (f)
    bool getMark();
};

#endif // SPOT_H
