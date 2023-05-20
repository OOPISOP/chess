#ifndef BOARD_H
#define BOARD_H

#include "Spot.h"
#include <vector>
#include <iostream>
<<<<<<< HEAD
=======

>>>>>>> 512f4a0 (f)
using namespace std;

class Board
{
private :
    int x;
    int y;
<<<<<<< HEAD
public:
    enum Types {
=======

public:
    enum Types
    {
>>>>>>> 512f4a0 (f)
        A_Pawn,
        A_Rook,
        A_Bishop,
        A_Knight,
        A_Queen,
        A_King
    };
    vector<vector<Spot>> boxes;
<<<<<<< HEAD
    Board();

    ~ Board();

    Board(const Board &sourceBoard);
    Spot getBox(int y,int x)const;
    void resetBoard();
    Spot findKing(bool isWhite);
=======
>>>>>>> 512f4a0 (f)
    bool whiteKingMoved = false;
    bool whiteLeftRookMoved = false;
    bool whiteRightRookMoved = false;
    bool blackKingMoved = false;
    bool blackLeftRookMoved = false;
    bool blackRightRookMoved = false;

<<<<<<< HEAD


=======
    Board();
    Board(const Board &sourceBoard);
    ~Board();

    Spot getBox(int y,int x) const;
    Spot* getBoxPointer(int y,int x);
    void resetBoard();
    Spot* findKing(bool isWhite);
>>>>>>> 512f4a0 (f)
};

#endif // BOARD_H
