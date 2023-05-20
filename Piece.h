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
    int type;
    bool moved = false;
    bool checked = false;
    bool promoting = false;
    bool enPassant = false;
    bool castling = false;
public:
    Piece(bool white,int type);
    Piece();
    virtual Piece* clone()const = 0;

    void setWhite(bool white);
    void setType(int type);
    void setMoved(bool moved);
    void setChecked(bool checked);
    void setPromoting(bool promoting);
    void setEnPassant(bool enPassant);
    void setCastling(bool castling);

    bool getWhite()const;
    int getType()const;
    bool getMoved()const;
    bool getChecked()const;
    bool getPromoting()const;
    bool getEnPassant()const;
    bool getCastling()const;

    virtual bool canMove(Board board,Spot start,Spot end) = 0;
};

#endif // PIECE_H
