#ifndef PIECE_H
#define PIECE_H

#include <string.h>
#include <iostream>
<<<<<<< HEAD
=======

>>>>>>> 512f4a0 (f)
using namespace std;

class Board;
class Spot;

class Piece
{
<<<<<<< HEAD

private:
    bool white = false;
    bool moved = false;
    int type;

    bool checked = false;

=======
private:
    bool white = false;
    int type;
    bool moved = false;
    bool checked = false;
>>>>>>> 512f4a0 (f)
    bool promoting = false;
    bool enPassant = false;
    bool castling = false;

<<<<<<< HEAD

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

=======
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
>>>>>>> 512f4a0 (f)
};

#endif // PIECE_H
