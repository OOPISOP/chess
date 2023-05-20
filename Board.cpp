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

Board::Board(const Board  &sourceBoard)
{
    this->x = sourceBoard.x;
    this->y = sourceBoard.y;
    this->boxes.clear();

    this->boxes.resize(8);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(sourceBoard.getBox(i,j).havePiece())
            {
                Spot spot(i,j,sourceBoard.getBox(i,j).getPiece()->clone());
                this->boxes[i].push_back(spot);
            }
            else
            {
                this->boxes[i].push_back(Spot(j,i));
            }
        }
    }
}

Board::~Board()
{
    this->boxes.clear();
    this->x = 0;
    this->y = 0;
    //delete this;
}

Spot Board::getBox(int y,int x) const
{
    if((x < 0) || (x > 7) || (y < 0) || (y > 7))
    {
        cout<<"Index out of bound"<<endl;
    }
    return boxes[y][x];
}

Spot* Board::getBoxPointer(int y,int x)
{
    if((x < 0) || (x > 7) || (y < 0) || (y > 7))
    {
        cout<<"Index out of bound"<<endl;
    }
    return &boxes[y][x];
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

Spot* Board::findKing(bool isWhite)
{
    // Declaration for variables.
    // Initialise.
    int startIndex = (isWhite) ? 7 : 0;
    int endIndex = (isWhite) ? -1 : 8;
    int deltaIndex = (isWhite) ? -1 : 1;
    Spot* kingsSpot;
    Piece* kingsPiece;

    // Find King.
    for (int row = startIndex; row != endIndex; row += deltaIndex)
    {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            kingsSpot = &boxes[row][col];
            kingsPiece = kingsSpot->getPiece();

            // King found.
            if (kingsSpot->havePiece() &&
                (kingsPiece->getWhite() == isWhite) &&
                (kingsPiece->getType() == A_King))
            {
                return kingsSpot;
            }
        }
    }
}
