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
    bool white = false;
    bool moved = false;
    int type;

    bool promoting = false;
    bool enPassant = false;
    bool castling = false;


public:
    Piece(bool white,int type);
    Piece();
    bool isWhite();
    void setWhite(bool white);
    bool isMoved();
    void setMoved(bool moved);
    int getType();
    void setType(int type);
    virtual bool canMove(Board board,Spot start,Spot end) = 0;

    void setPromoting(bool promoting);
    bool isPromoting();
    void setEnPassant(bool enPassant);
    bool isEnPassant();
    void setCastling(bool castling);
    bool isCastling();
};

#endif // PIECE_H
