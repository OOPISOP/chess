/***********************************************************************
 * File: King.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: King piece imp
***********************************************************************/
#include "King.h"

King::King(bool white,int type) : Piece(white,type)
{
}

Piece* King::clone()const
{
    return new King(*this);
}
//Intent:can move
//Pre:board start end spot
//Pos:return bool
bool King::canMove(Board board,Spot start,Spot end)
{

    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->getWhite() == this->getWhite())
    {
        return false;
    }

    // Declaration for informative variables.
    int deltaX = end.getX() - start.getX();
    int deltaY = end.getY() - start.getY();

    // Can move within the 3 by 3 square.
    if ((abs(deltaX) <= 1) && (abs(deltaY) <= 1) && !((deltaX == 0) && (deltaY == 0)))
    {
        return true;
    }

    return isValidCastling(board,start,end);
}
//Intent:castle
//Pre:board start end spot
//Pos:return bool if can castle
bool King::isValidCastling(Board board,Spot start,Spot end)
{
    Spot startBox = board.getBox(start.getY(),start.getX());
    Piece* startPiece = startBox.getPiece();


    if(startPiece->getType()!=5||(startPiece->getWhite()&&board.whiteKingMoved)||((!startPiece->getWhite()&&board.blackKingMoved)))
    {
        return false;
    }

    int deltaY = end.getY() - start.getY();
    int deltaX = end.getX() - start.getX();

    if(deltaY!=0||abs(deltaX)!=2)
    {
        return false;
    }
    int rookX = (deltaX>0)?7:0;
    bool rookMoved = false;

    if(startPiece->getWhite())
    {
        rookMoved = (deltaX>0)?board.whiteRightRookMoved:board.whiteLeftRookMoved;
    }
    else
    {
        rookMoved = (deltaX>0)?board.blackRightRookMoved:board.blackLeftRookMoved;
    }
    Spot rookStartBox =  board.getBox(end.getY(),rookX);

    if(!rookStartBox.havePiece()||rookStartBox.getPiece()->getType()!=1||rookMoved)
    {
        return false;
    }

    Spot rookEndBox = board.getBox(end.getY(),end.getX() - ((deltaX>0)?1:-1));

    if(!rookStartBox.getPiece()->canMove(board,rookStartBox,rookEndBox))
    {
        return false;
    }


    return true;
}

