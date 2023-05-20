#ifndef BOARD_H
#define BOARD_H

#include "Spot.h"
#include <vector>
#include <iostream>

using namespace std;

class Board
{
private :
    int x;
    int y;


public:
    enum Types
    {

        A_Pawn,
        A_Rook,
        A_Bishop,
        A_Knight,
        A_Queen,
        A_King
    };
    vector<vector<Spot>> boxes;
    bool whiteKingMoved = false;
    bool whiteLeftRookMoved = false;
    bool whiteRightRookMoved = false;
    bool blackKingMoved = false;
    bool blackLeftRookMoved = false;
    bool blackRightRookMoved = false;

    Board();
    Board(const Board &sourceBoard);
    ~Board();

    Spot getBox(int y,int x) const;
    Spot* getBoxPointer(int y,int x);
    void resetBoard();
    Spot* findKing(bool isWhite);
};

#endif // BOARD_H
