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
Board::Board(const Board &sourceBoard)
{
    this->x = sourceBoard.x;
    this->y = sourceBoard.y;
    this->boxes = sourceBoard.boxes;
}
Spot Board::getBox(int y,int x) const
{

    if(x < 0 || x > 7 || y < 0 || y > 7)
    {
        cout<<"Index out of bound"<<endl;
        return boxes[0][0];
    }
    return boxes[y][x];
}
void Board::resetBoard()
{
    //clear the boxes
    boxes.clear();
    //resize the boxes
    boxes.resize(8);
    boxes[0].push_back(Spot(0,0,new Rook(false,A_Rook)));
    boxes[0].push_back(Spot(1,0,new Knight(false,A_Knight)));
    boxes[0].push_back(Spot(2,0,new Bishop(false,A_Bishop)));
    boxes[0].push_back(Spot(3,0,new King(false,A_King)));
    boxes[0].push_back(Spot(4,0,new Queen(false,A_Queen)));
    boxes[0].push_back(Spot(5,0,new Bishop(false,A_Bishop)));
    boxes[0].push_back(Spot(6,0,new Knight(false,A_Knight)));
    boxes[0].push_back(Spot(7,0,new Rook(false,A_Rook)));
    for(int i=0;i<8;i++)
    {
        boxes[1].push_back(Spot(i,1,new Pawn(false,A_Pawn)));
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
        boxes[6].push_back(Spot(i,6,new Pawn(true,A_Pawn)));
    }
    boxes[7].push_back(Spot(0,7,new Rook(true,A_Rook)));
    boxes[7].push_back(Spot(1,7,new Knight(true,A_Knight)));
    boxes[7].push_back(Spot(2,7,new Bishop(true,A_Bishop)));
    boxes[7].push_back(Spot(3,7,new King(true,A_King)));
    boxes[7].push_back(Spot(4,7,new Queen(true,A_Queen)));
    boxes[7].push_back(Spot(5,7,new Bishop(true,A_Bishop)));
    boxes[7].push_back(Spot(6,7,new Knight(true,A_Knight)));
    boxes[7].push_back(Spot(7,7,new Rook(true,A_Rook)));
}
