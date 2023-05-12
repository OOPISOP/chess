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
    enum Types {
        A_Pawn,
        A_Rook,
        A_Bishop,
        A_Knight,
        A_Queen,
        A_King
    };
    vector<vector<Spot>> boxes;
    Board();
    Spot getBox(int y,int x)const;
    void resetBoard();
};

#endif // BOARD_H
