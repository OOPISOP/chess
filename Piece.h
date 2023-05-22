/***********************************************************************
 * File: Piece.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Piece abstract class define
***********************************************************************/
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
    virtual Piece* clone()const = 0;//clone the piece

    void setWhite(bool white);//set white side
    void setType(int type);//set piece type
    void setMoved(bool moved);//set moved
    void setChecked(bool checked);//set checked
    void setPromoting(bool promoting);//set promoting
    void setEnPassant(bool enPassant);//set en passant
    void setCastling(bool castling);//set castling

    bool getWhite()const;//get white
    int getType()const;//get type
    bool getMoved()const;//get moved
    bool getChecked()const;//get checked
    bool getPromoting()const;//get promoting
    bool getEnPassant()const;//get en passant
    bool getCastling()const;//get castling

    virtual bool canMove(Board board,Spot start,Spot end) = 0;//virtual function can  move
};

#endif // PIECE_H
