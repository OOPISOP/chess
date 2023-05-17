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

    bool checked = false;

    bool promoting = false;
    bool enPassant = false;
    bool castling = false;


public:
    Piece(bool white,int type);
    Piece();
    bool isWhite()const;
    void setWhite(bool white);

    bool isMoved()const;
    void setMoved(bool moved);
    int getType()const;
    void setType(int type);
    virtual bool canMove(Board board,Spot start,Spot end) = 0;

    virtual Piece* clone()const = 0;
    bool isChecked()const;
    void setChecked(bool checked);

    void setPromoting(bool promoting);
    bool isPromoting()const;
    void setEnPassant(bool enPassant);
    bool isEnPassant()const;
    void setCastling(bool castling);
    bool isCastling()const;

};

#endif // PIECE_H
