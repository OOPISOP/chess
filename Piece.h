#ifndef PIECE_H
#define PIECE_H

#include <string.h>
#include <iostream>
using namespace std;

class Board;
class Spot;

class Piece
{
    private:
    bool killed = false;
    bool white = false;
    int type;
public:
    Piece(bool white,int type);
    Piece();
    bool isWhite();
    void setWhite(bool white);
    bool isKilled();
    void setKilled(bool killed);
    int getType();
    void setType(int type);
    virtual bool canMove(Board board,Spot start,Spot end) = 0;
};

#endif // PIECE_H
