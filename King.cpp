#include "King.h"

King::King(bool white,int type) : Piece(white,type)
{

}
bool King::canMove(Board board,Spot start,Spot end)
{
    // Check checkmate.
    // isCheckMate();

    // Cannot kill ally.
    if(end.havePiece() && end.getPiece()->isWhite() == this->isWhite())
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


bool King::isValidCastling(Board board,Spot start,Spot end)
{
    Spot startBox = board.getBox(start.getY(),start.getX());
    Piece* startPiece = startBox.getPiece();
    if(startPiece->getType()!=5||(startPiece->isWhite()&&board.whiteKingMoved)||((!startPiece->isWhite()&&board.blackKingMoved)))
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
    if(startPiece->isWhite())
    {
        rookMoved = (deltaX>0)?board.whiteRightRookMoved:board.blackRightRookMoved;
    }
    else
    {
        rookMoved = (deltaX>0)?board.blackLeftRookMoved:board.blackLeftRookMoved;
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
//    if(seeCheck(board,start.getPiece()->isWhite(),board.findKing(start.getPiece()->isWhite())))
//    {
//        return false;
//    }
    return true;
}

bool King::seeCheck(Board board,bool white,Spot enemyKingsSpot)
{
    // Initialise.
    int startIndex = (white) ? 7 : 0;
    int endIndex = (white) ? -1 : 8;
    int deltaIndex = (white) ? -1 : 1;

    // Find possible attck to enemy's king.
    for (int row = startIndex; row != endIndex; row += deltaIndex)
    {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot tempSpot = board.getBox(row, col);
            Piece *tempPiece = tempSpot.getPiece();

            // Possible attack found.
            if (tempSpot.havePiece() &&
                (tempPiece->isWhite() == white) /*&&
                (canReallyMove(tempSpot, enemyKingsSpot))*/)
            {
                board.boxes[enemyKingsSpot.getY()][enemyKingsSpot.getX()].getPiece()->setChecked(true);
                return true;
            }
        }
    }

    // If there is no any available attack to the enemy's king, cancel check.
    board.boxes[enemyKingsSpot.getY()][enemyKingsSpot.getX()].getPiece()->setChecked(false);
    return false;
}
Piece* King::clone()const
{
    return new King(*this);
}
