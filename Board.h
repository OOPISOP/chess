/***********************************************************************
 * File: Board.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Chess Board define
***********************************************************************/
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

    Spot getBox(int y,int x) const;//get board spot
    Spot* getBoxPointer(int y,int x);//get board spot pointer
    void resetBoard();//reset chess board
    Spot* findKing(bool isWhite);//find king
};

#endif // BOARD_H
