/***********************************************************************
 * File: Spot.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Spot define
***********************************************************************/
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
    bool enPassant;

public:
    Spot(int x,int y,Piece* piece);
    Spot(int x,int y);

    void setPiece(Piece* p);//set piece
    void setPiece();//set piece
    void setX(int x);//set x
    void setY(int y);//set y
    void setMark(bool mark);//set spot mark
    void setEnPassant(bool enPassnat);

    Piece* getPiece()const;//get piece
    int getX()const;//get x
    int getY()const;//get y
    bool havePiece()const;//have piece
    bool getMark();//get mark
    bool getEnPassant()const;
};

#endif // SPOT_H
