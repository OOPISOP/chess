#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"

Board::Board()
{
    this->resetBoard();
}
Spot Board::getBox(int x,int y) const
{
    if(x < 0 || x > 7 || y < 0 || y > 7)
    {
        cout<<"Index out of bound"<<endl;
    }
    return boxes[x][y];
}
void Board::resetBoard()
{
    //clear the boxes
    boxes.clear();
    //resize the boxes
    boxes.resize(8);
    boxes[0].push_back(Spot(0,0,Rook(false,A_Rook)));
    boxes[0].push_back(Spot(1,0,Knight(false,A_Knight)));
    boxes[0].push_back(Spot(2,0,Bishop(false,A_Bishop)));
    boxes[0].push_back(Spot(3,0,King(false,A_King)));
    boxes[0].push_back(Spot(4,0,Queen(false,A_Queen)));
    boxes[0].push_back(Spot(5,0,Bishop(false,A_Bishop)));
    boxes[0].push_back(Spot(6,0,Knight(false,A_Knight)));
    boxes[0].push_back(Spot(7,0,Rook(false,A_Rook)));
    for(int i=0;i<8;i++)
    {
        boxes[1].push_back(Spot(i,1,Pawn(false,A_Pawn)));
    }
    for(int i=2;i<6;i++)
    {
        for(int j=0;j<8;j++)
        {
            boxes[i].push_back(Spot(j,i));
        }
    }
    for(int i=0;i<8;i++)
    {
        boxes[6].push_back(Spot(i,6,Pawn(true,A_Pawn)));
    }
    boxes[7].push_back(Spot(0,7,Rook(true,A_Rook)));
    boxes[7].push_back(Spot(1,7,Knight(true,A_Knight)));
    boxes[7].push_back(Spot(2,7,Bishop(true,A_Bishop)));
    boxes[7].push_back(Spot(3,7,King(true,A_King)));
    boxes[7].push_back(Spot(4,7,Queen(true,A_Queen)));
    boxes[7].push_back(Spot(5,7,Bishop(true,A_Bishop)));
    boxes[7].push_back(Spot(6,7,Knight(true,A_Knight)));
    boxes[7].push_back(Spot(7,7,Rook(true,A_Rook)));
}
