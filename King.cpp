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
    if(seeCheck(board,start))
    {
        return false;
    }
    return true;
}

bool King::seeCheck(Board board,Spot start)
{
    // Declaration for variables.
    int startIndex = (start.getPiece()->isWhite()) ? 0 : 7;
    int endIndex = (start.getPiece()->isWhite()) ? 8 : -1;
    int deltaIndex = (start.getPiece()->isWhite()) ? 1 : -1;
    Spot kingsSpot(0,0);
    Piece* kingsPiece;

    // Find enemy's King.
    for (int row = startIndex; row != endIndex; row += deltaIndex)
    {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            kingsSpot = board.getBox(row, col);
            kingsPiece = kingsSpot.getPiece();

            // King found.
            if (kingsSpot.havePiece() &&
                (kingsPiece->isWhite() != start.getPiece()->isWhite()) &&
                (kingsPiece->getType() == 5))
            {
                // Break searching.
                row = (endIndex - deltaIndex);
                break;
            }
        }
    }

    // Initialise index variables oppositely.
    startIndex = (start.getPiece()->isWhite()) ? 7 : 0;
    endIndex = (start.getPiece()->isWhite()) ? -1 : 8;
    deltaIndex = (start.getPiece()->isWhite()) ? -1 : 1;

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
                (tempPiece->isWhite() == start.getPiece()->isWhite()) &&
                (tempPiece->canMove(board, tempSpot, kingsSpot)))
            {
                kingsPiece->setChecked(true);
                return true;
            }
        }
    }
    return false;
}
