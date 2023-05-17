/***********************************************************************
 * File: Game.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: Brendon
 * Update Date: 2023/05/10
 * Description: Game
***********************************************************************/
#include "Game.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Spot.h"
#include <queue>
#include <QQuickView>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QtQuick/QQuickItem>
#include <sstream>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>


//Intent:init the Game class
//Pre:p1 p2 is Player respect player,and push back to players ,respect have two player,and set the current player
//Pos:set two player and current turn
Game::Game(QObject *parent) : QAbstractListModel(parent)
{
    newGame(true);
}

Game::~Game()
{
    this->players.clear();
}
//Intent:creat  the new Game
//Pre:p1 p2 is Player represent player,and push back to players ,represent have two player,and set the current player
//Pos:set two player and current turn
void Game::newGame(bool white)
{
    board.resetBoard();
    Player p1,p2;
    p1.setSide(white);
    p2.setSide(!white);
    this->players.push_back(p1);
    this->players.push_back(p2);
    this->currentTurn = p1;
    this->enPassant = make_pair(-1,-1);
    this->castleRook = make_pair(-1,-1);
    this->fenList.clear();
    this->recordIndex = -1;
    this->effect.setVolume(1.f);
    recordFEN();
    castleStatusList.clear();
}

void Game::resetAllMark()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            Spot* spot = &this->board.boxes[i][j];
            spot->setMark(false);
        }
    }
}


void Game::showNextMove(int x,int y )
{
    emit dataChanged(index(0),index(63));
    resetAllMark();
    Spot* startBox = &this->board.boxes[y][x];

    if(!startBox->havePiece())
    {
        cout<<"not Piece"<<endl;
        return ;
    }

    Piece* sourcePiece = startBox->getPiece();

    if(sourcePiece->isWhite() != currentTurn.isWhiteSide())
    {
        cout<<"not your turn"<<endl;
        return;
    }
    // The input surround poistion
    int dir[8][2] = { {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0} };
    int dirKnight[8][2] =  { {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1} };
    if(sourcePiece->getType() == 3)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<2;j++)
            {
                dir[i][j] = dirKnight[i][j];
            }
        }
    }
    queue<pair<int, int>> que;
    vector<vector<bool>> vis(8,vector<bool>(8,false));
    que.push(pair<int, int>(x, y));
    while(!que.empty())
    {
        int x = que.front().first;
        int y = que.front().second;
        que.pop();
        for(int i=0;i<8;i++)
        {
            int nextX = x + dir[i][0];
            int nextY = y + dir[i][1];
            if((nextX>7)||(nextX<0)||(nextY>7)||(nextY<0))continue;
            Spot* endBox = &this->board.boxes[nextY][nextX];
            if(canReallyMove(*startBox,*endBox) && !vis[nextX][nextY])

            {
                endBox->setMark(true);
                que.push(pair<int, int>(nextX, nextY));
            }
            vis[nextX][nextY] = true;
        }
    }
   emit dataChanged(index(0),index(63));
}


Spot Game::FindKing(bool isWhite)
{
   // Declaration for variables.
   // Initialise.
   int startIndex = (isWhite) ? 7 : 0;
   int endIndex = (isWhite) ? -1 : 8;
   int deltaIndex = (isWhite) ? -1 : 1;
   Spot kingsSpot(0,0);
   Piece* kingsPiece;

   // Find King.
   for (int row = startIndex; row != endIndex; row += deltaIndex)
   {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            kingsSpot = board.getBox(row, col);
            kingsPiece = kingsSpot.getPiece();

            // King found.
            if (kingsSpot.havePiece() &&
                (kingsPiece->isWhite() == isWhite) &&
                (kingsPiece->getType() == King))
            {
                return kingsSpot;
            }
        }
   }
}

bool Game::seeCheck(Spot enemyKingsSpot)
{
   // Initialise.
   int startIndex = (currentTurn.isWhiteSide()) ? 7 : 0;
   int endIndex = (currentTurn.isWhiteSide()) ? -1 : 8;
   int deltaIndex = (currentTurn.isWhiteSide()) ? -1 : 1;

   // Find possible attack to enemy's king.
   for (int row = startIndex; row != endIndex; row += deltaIndex)
   {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot tempSpot = board.getBox(row, col);
            Piece *tempPiece = tempSpot.getPiece();

            // Possible attack found.
            if (tempSpot.havePiece() &&
                (tempPiece->isWhite() == currentTurn.isWhiteSide()) &&
                (canReallyMove(tempSpot, enemyKingsSpot)))
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

bool Game::seeCheckmate()
{
   Spot tempSpot = FindKing(!currentTurn.isWhiteSide());
   Spot *enemyKingsSpot = &this->board.boxes[tempSpot.getY()][tempSpot.getX()];

   // No checkmate without being checked.
   if (!enemyKingsSpot->getPiece()->isChecked())
   {
        return false;
   }

   // Declaration.
   int directions[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

   // No checkmate when enemy King has valid move.
   for (int i = 0; i < 8; i++)
   {
        // Initialise.
        int nextX = enemyKingsSpot->getX() + directions[i][0];
        int nextY = enemyKingsSpot->getY() + directions[i][1];

        // Skip if out of range.
        if ((nextX > 7) || (nextX < 0) || (nextY > 7) || (nextY < 0))
        {
            continue;
        }

        // Initialise.
        Spot tempSpot(nextX,nextY);

        // Enemy King has valid move to avoid checkmate.
        if (canReallyMove(*enemyKingsSpot, tempSpot))
        {
            return false;
        }
   }

   // Initialise index variables.
   int startIndex = (currentTurn.isWhiteSide()) ? 0 : 7;
   int endIndex = (currentTurn.isWhiteSide()) ? 8 : -1;
   int deltaIndex = (currentTurn.isWhiteSide()) ? 1 : -1;

   // No checkmate when enemy's piece can block checkmate.
   for (int row = startIndex; row != endIndex; row += deltaIndex)
   {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot enemySpot = board.getBox(row, col);
            Piece *enemyPiece = enemySpot.getPiece();

            // Enemy found.
            if (enemySpot.havePiece() &&
                (enemyPiece->isWhite() != currentTurn.isWhiteSide()))
            {
                // See every move can enemy made.
                for (int row2 = startIndex; row2 != endIndex; row2 += deltaIndex)
                {
                    for (int col2 = startIndex; col2 != endIndex; col2 += deltaIndex)
                    {
                        // Initialise.
                        Spot tempSpot(row2, col2);

                        if (enemyPiece->canMove(board, enemySpot, tempSpot))
                        {
                            // Declaration for variables.
                            Board tempBoard(board);

                            // Simulate next situation.
                            makeMoveSimulator(tempBoard, enemySpot, tempSpot);

                            // Found way to block checkmate.
                            if (!isCheckmateMove(tempBoard, !currentTurn.isWhiteSide()))
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
   }

   return true;
}

bool Game::isCheckmateMove(Board tempBoard, bool isWhite)
{
   Spot kingsSpot = FindKing(isWhite);

   // Initialise.
   int startIndex = (isWhite) ? 0 : 7;
   int endIndex = (isWhite) ? 8 : -1;
   int deltaIndex = (isWhite) ? 1 : -1;

   // Find possible attack from enemy.
   for (int row = startIndex; row != endIndex; row += deltaIndex)
   {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot tempSpot = tempBoard.getBox(row, col);
            Piece *tempPiece = tempSpot.getPiece();

            // Enemy found way to attack King.
            if (tempSpot.havePiece() &&
                (tempPiece->isWhite() != isWhite) &&
                tempPiece->canMove(tempBoard, tempSpot, kingsSpot))
            {
                return true;
            }
        }
   }

   return false;
}

bool Game::canReallyMove(Spot start, Spot end)
{
   if (start.getPiece()->canMove(board, start, end))
   {
        // Declaration for variables.
        Board tempBoard(board);

        // Simulate next situation.
        makeMoveSimulator(tempBoard, start, end);

        if (!isCheckmateMove(tempBoard, currentTurn.isWhiteSide()))
        {
            return true;
        }
        else
        {
            // PLAY KING DANGEROUS SOUND
        }
   }

   return false;
}

void Game::makeMoveSimulator(Board &tempBoard, Spot start, Spot end)
{
   Spot* startBox = &tempBoard.boxes[start.getY()][start.getX()];
   Spot* endBox = &tempBoard.boxes[end.getY()][end.getX()];
   Piece* sourcePiece = startBox->getPiece();

   if(isCastle(start.getX(),start.getY(),end.getX(),end.getY()))
   {
        Spot* rookSpot = &tempBoard.boxes[castleRook.second][castleRook.first];
        Piece* rookPiece = rookSpot->getPiece();
        int rookTargetX = (end.getX()-start.getX())>0?end.getX() - 1  : end.getX() + 1;
        Spot* targetSpot = &tempBoard.boxes[end.getY()][rookTargetX];
        targetSpot->setPiece(rookPiece);
        rookSpot->setPiece();
   }

   if(!endBox->havePiece())
   {
        endBox->setPiece(sourcePiece);
        startBox->setPiece();
   }
   else
   {
        endBox->setPiece(sourcePiece);
        startBox->setPiece();
   }

   if(endBox->getPiece()->getType()==King)
   {
        if(currentTurn.isWhiteSide())
        {
            tempBoard.whiteKingMoved = true;
        }
        else
        {
            tempBoard.blackKingMoved = true;
        }
   }

   if(endBox->getPiece()->getType()==Rook)
   {
        if(currentTurn.isWhiteSide())
        {
            if(start.getX() == 0)
            {
                tempBoard.whiteLeftRookMoved = true;
            }
            else if(start.getX() == 7)
            {
                tempBoard.whiteRightRookMoved = true;
            }
        }
        else
        {
            if(start.getX() == 0)
            {
                tempBoard.blackLeftRookMoved = true;
            }
            else if(start.getX() == 7)
            {
                tempBoard.blackRightRookMoved = true;
            }
        }
   }

   Spot* near = &tempBoard.boxes[start.getY()][start.getX()+ (end.getX() - start.getX())];

   if(near->havePiece()&&near->getPiece()->isEnPassant())
   {
        near->setPiece();
   }
   else
   {
        if(this->enPassant.first > 0 && this->enPassant.second > 0)
        {
            Spot* enPassantSpot = &tempBoard.boxes[8 - this->enPassant.second][this->enPassant.first];
            Piece* enPassantPiece = enPassantSpot->getPiece();
            enPassantPiece->setEnPassant(false);
        }
   }
   if(isEnPassant(start.getX(),start.getY(),end.getX(),end.getY()))
   {
        sourcePiece->setEnPassant(true);
   }
}


//Intent:make move
//Pre:startX and startY represent start X and Y,and endX and endY represent end X and Y
//Pos:can move return true,or false
bool Game::makeMove(int startX,int startY,int endX,int endY)
{
    Spot* startBox = &this->board.boxes[startY][startX];
    Spot* endBox = &this->board.boxes[endY][endX];

    if(!startBox->havePiece())
    {
        cout<<"not Piece"<<endl;
        return false;
    }

    Piece* sourcePiece = startBox->getPiece();

    if(sourcePiece->isWhite() != currentTurn.isWhiteSide())
    {
        cout<<"not your turn"<<endl;
        return false;
    }
    if(!canReallyMove(*startBox,*endBox))
    {
        cout<<"can't move"<<endl;
        return false;
    }

    if(isCastle(startX,startY,endX,endY))
    {
        Spot* rookSpot = &this->board.boxes[castleRook.second][castleRook.first];
        Piece* rookPiece = rookSpot->getPiece();
        int rookTargetX = (endX-startX)>0?endX - 1  : endX + 1;
        Spot* targetSpot = &this->board.boxes[endY][rookTargetX];
        targetSpot->setPiece(rookPiece);
        rookSpot->setPiece();
        castleRook = make_pair(-1,-1);
    }

    if(!endBox->havePiece())
    {
        endBox->setPiece(sourcePiece);
        startBox->setPiece();
    }
    else
    {
        endBox->setPiece(sourcePiece);
        startBox->setPiece();
    }

    if(endBox->getPiece()->getType()==King)
    {
        if(currentTurn.isWhiteSide())
        {
            board.whiteKingMoved = true;
        }
        else
        {
            board.blackKingMoved = true;
        }
    }
    if(endBox->getPiece()->getType()==Rook)
    {
        if(currentTurn.isWhiteSide())
        {
            if(startX == 0)
            {
                board.whiteLeftRookMoved = true;
            }
            else if(startX == 7)
            {
                board.whiteRightRookMoved = true;
            }
        }
        else
        {
            if(startX == 0)
            {
                board.blackLeftRookMoved = true;
            }
            else if(startX == 7)
            {
                board.blackRightRookMoved = true;
            }
        }
    }

    Spot* near = &this->board.boxes[startY][startX+ (endX - startX)];

    if(near->havePiece()&&near->getPiece()->isEnPassant())
    {
        near->setPiece();
    }
    else
    {
        if(this->enPassant.first > 0 && this->enPassant.second > 0)
        {
            Spot* enPassantSpot = &this->board.boxes[8 - this->enPassant.second][this->enPassant.first];
            Piece* enPassantPiece = enPassantSpot->getPiece();
            enPassantPiece->setEnPassant(false);
        }
    }
    if(isEnPassant(startX,startY,endX,endY))
    {
        sourcePiece->setEnPassant(true);
        this->enPassant = make_pair(endX,8 - endY);
    }
    else
    {
        this->enPassant = make_pair(-1,-1);
    }

    bool statusCheck = seeCheck(FindKing(!currentTurn.isWhiteSide()));

    if (statusCheck)
    {
        // PLAY CHECK SOUND.
    }
    seeCheckmate();
    if (status == CHECKMATE)
    {
        if (statusCheck)
        {
//            (currentTurn.isWhiteSide ()) ? BLACK_WIN : WHITE_WIN;
            cout << "WIN/LOSE" << endl;
            return false;
        }
        else
        {
            status = STALEMATE;
            cout << "DRAW" << endl;
            return false;
        }
    }
// else if resignation.


    if (sourcePiece->getType() == Pawn &&(endY==0 || endY == 7) )
    {
        //promotion
        emit showPopup(endX,endY,sourcePiece->isWhite());
    }

    if(this->currentTurn == players[0])
    {
        this->currentTurn = players[1];
    }
    else
    {
        this->currentTurn = players[0];
    }
    playChessSound();
    resetAllMark();
    recordFEN();
    beginResetModel();
    endResetModel();
    return true;
}

void Game::playChessSound()
{
    QString soundSource = p1ChessSound;
    if(currentTurn == players[1])
    {
        soundSource = p2ChessSound;
    }
    effect.setSource(QUrl::fromLocalFile(soundSource));
    effect.play();
}

bool Game::isCastle(int startX,int startY,int endX,int endY)
{
    Spot* startBox = &this->board.boxes[startY][startX];
    Piece* startPiece = startBox->getPiece();
    if(startPiece->getType()!=King||(startPiece->isWhite()&&board.whiteKingMoved)||((!startPiece->isWhite()&&board.blackKingMoved)))
    {
         return false;
    }
    int deltaY = endY - startY;
    int deltaX = endX - startX;
    if(deltaY!=0||abs(deltaX)<2)
    {
         return false;
    }
    castleRook = make_pair((deltaX>0)?7:0,endY);
    return true;
}

bool Game::isEnPassant(int startX,int startY,int endX,int endY)
{
    if(abs(endY - startY) != 2 || endX != startX)
    {
        return false;
    }
    return true;
}

//Intent:Pawn Promotion
//Pre:x y and type
//Post:that Pawn Promotion
void Game::promotion(int x,int y,int type)
{
    Spot* spot = &this->board.boxes[y][x];
    Piece* piece = spot->getPiece();
    bool white = piece->isWhite();
    if(type==0)
    {
        spot->setPiece(new class Rook(white,1));
    }
    else if(type == 1)
    {
        spot->setPiece(new class Bishop(white,2));
    }
    else if(type == 2)
    {
        spot->setPiece(new class Knight(white,3));
    }
    else if(type == 3)
    {
        spot->setPiece(new class Queen(white,4));
    }
    beginResetModel();
    endResetModel();
}


void Game::recordFEN()
{
    //FEN:k7/pppppppp/8/8/8/8/PPPPPPPP/K7 b - - 0 1
    string fen = "";
    for(int i=0;i<8;i++)
    {
        int  emptyCount = 0;
        for(int j=0;j<8;j++)
        {
            const Spot* SPOT = &this->board.boxes[i][j];
            const Piece* PIECE = SPOT->getPiece();
            if(!SPOT->havePiece())
            {
                emptyCount++;
                continue;
            }
            if(emptyCount>0)
            {
                fen += to_string(emptyCount);
                emptyCount = 0;
            }
            if(PIECE->isWhite())
            {
                fen += "PRBNQK"[PIECE->getType()];
            }
            else
            {
                fen += "prbnqk"[PIECE->getType()];
            }
        }
        if(emptyCount > 0)
        {
            fen += to_string(emptyCount);
        }
        if(i < 7)
        {
            fen += "/";
        }
    }
    fen += " ";
    if(currentTurn.isWhiteSide())
    {
        fen += "w";
    }
    else
    {
        fen += "b";
    }
    fen += " ";
    string castling = "";
    KingAndRookStatus castleStatus;
    castleStatus.whiteKingMoved = board.whiteKingMoved;
    castleStatus.whiteLeftRookMoved = board.blackLeftRookMoved;
    castleStatus.whiteRightRookMoved = board.blackRightRookMoved;
    castleStatus.blackKingMoved = board.blackLeftRookMoved;
    castleStatus.blackLeftRookMoved = board.blackLeftRookMoved;
    castleStatus.blackRightRookMoved = board.blackRightRookMoved;
    if (!board.whiteKingMoved)
    {
        if (!board.whiteLeftRookMoved) castling += "K";
        if (!board.whiteRightRookMoved) castling += "Q";
    }
    if (!board.blackKingMoved)
    {
        if (!board.blackLeftRookMoved) castling += "k";
        if (!board.blackRightRookMoved) castling += "q";
    }
    if (castling.empty())
    {
        fen += "-";
    } else
    {
        fen += castling;
    }
    fen += " ";
    if(this->enPassant.first < 0 || this->enPassant.second < 0)
    {
        fen += "-";
    }
    else
    {
        fen += 'a' + this->enPassant.first;
        fen += '0' + this->enPassant.second;
    }
    if(recordIndex < (int)this->fenList.size()-1)
    {
        this->fenList.resize(recordIndex+1);
        this->castleStatusList.resize(recordIndex+1);
    }
    this->fenList.push_back(fen);
    this->castleStatusList.push_back(castleStatus);
    cout<<fen<<endl;
    this->recordIndex++;
}

bool Game::setFEN(QString fen)
{
    this->enPassant = make_pair(-1,-1);
    this->castleRook = make_pair(-1,-1);
    this->fenList.clear();
    this->recordIndex = -1;
    this->effect.setVolume(1.f);
    castleStatusList.clear();
    KingAndRookStatus status;
    setGame(fen.toStdString(),status);
    recordFEN();
    return true;
}


void Game::setBoardFromFEN(string fen)
{
    int i=0,j=0;
    for(const auto& f : fen)
    {
        if( f== '/')
        {
            i++;
            j=0;
        }
        if(j>7||j>7)break;
        if(isdigit(f))
        {
            int n = f - '0';
            while(n--)
            {
                Spot spot(j,i);
                this->board.boxes[i][j] = spot;
                j++;
            }
        }
        if(isalpha(f))
        {
            Spot spot(j,i);
                //P R B  N Q K
            switch(f)
            {
            case 'p':
                spot.setPiece(new class Pawn(false,0));
                break;
            case 'r':
                spot.setPiece(new class Rook(false,1));
                break;
            case 'b':
                spot.setPiece(new class Bishop(false,2));
                break;
            case 'n':
                spot.setPiece(new class Knight(false,3));
                break;
            case 'q':
                spot.setPiece(new class Queen(false,4));
                break;
            case 'k':
                spot.setPiece(new  class King(false,5));
                break;
            case 'P':
                spot.setPiece(new class Pawn(true,0));
                break;
            case 'R':
                spot.setPiece(new class Rook(true,1));
                break;
            case 'B':
                spot.setPiece(new class Bishop(true,2));
                break;
            case 'N':
                spot.setPiece(new class Knight(true,3));
                break;
            case 'Q':
                spot.setPiece(new class Queen(true,4));
                break;
            case 'K':
                spot.setPiece(new  class King(true,5));
                break;
            default:
                cout<<"error piece type"<<endl;
                break;
            }
            this->board.boxes[i][j] = spot;
            j++;
        }
    }
    beginResetModel();
    endResetModel();
}

void Game::updateKingRook(string fen)
{
    cout<<fen<<endl;
    if(fen!="-")
    {
        if(fen.find('K')!=string::npos&&fen.find('Q')!=string::npos)
        {
            this->board.whiteKingMoved = false;
        }
        if(fen.find('k')!=string::npos&&fen.find('q')!=string::npos)
        {
             this->board.blackKingMoved = false;
        }
        this->board.whiteRightRookMoved = !(fen.find("K") != string::npos);
        this->board.whiteLeftRookMoved = !(fen.find("Q") != string::npos);
        this->board.blackRightRookMoved = !(fen.find("k") != string::npos);
        this->board.blackLeftRookMoved = !(fen.find("q") != string::npos);
    }
    else
    {
        this->board.whiteKingMoved = true;
        this->board.blackKingMoved = true;
    }
}

void Game::setGame(string fen,KingAndRookStatus status)
{
    vector<std::string> parts;
    stringstream ss(fen);
    string part;
    while (getline(ss, part, ' '))
    {
        parts.push_back(part);
    }
    setBoardFromFEN(parts[0]);
    Player p1,p2;
    p1.setSide(true);
    p2.setSide(false);
    this->players.push_back(p1);
    this->players.push_back(p2);
    currentTurn = (parts[1] == "w") ? p1 : p2;
    updateKingRook(parts[2]);
    if(recordIndex>=0)
    {
        setCastleFromFEN(status);
    }
    if (parts[3] != "-")
    {
        int file = parts[3][0] - 'a';
        int rank = 8 - (parts[3][1] - '0') ;
        this->enPassant = make_pair(file, rank);
        if(file>7||file<0||rank>7||rank<0)
        {
            cout<<"en Passant error pos"<<endl;
        }
        Spot* spot = &this->board.boxes[rank][file];
        Piece* piece = spot->getPiece();
        piece->setEnPassant(true);
    }

    beginResetModel();
    endResetModel();
}

void Game::setCastleFromFEN(KingAndRookStatus status)
{
    board.whiteKingMoved = status.whiteKingMoved;
    board.whiteLeftRookMoved = status.whiteLeftRookMoved;
    board.whiteRightRookMoved = status.whiteRightRookMoved;
    board.blackKingMoved = status.blackKingMoved;
    board.blackLeftRookMoved = status.blackLeftRookMoved;
    board.blackRightRookMoved = status.blackRightRookMoved;
}

void Game::redo()
{
    if(recordIndex >= (int)fenList.size() - 1)
    {
        return ;
    }
    recordIndex++;
    cout<<fenList[recordIndex]<<endl;
    setGame(fenList[recordIndex],castleStatusList[recordIndex]);
}

void Game::undo()
{
    if(recordIndex <= 0)
    {
        return ;
    }
    recordIndex--;
    cout<<fenList[recordIndex]<<endl;
    setGame(fenList[recordIndex],castleStatusList[recordIndex]);
}


int Game::rowCount(const QModelIndex & ) const {
    return (board.boxes.size()*board.boxes[0].size());
}

QVariant Game::data(const QModelIndex & modelIndex, int role) const
{
    if (!modelIndex.isValid()) {
        return (QVariant());
    }

    int index = static_cast<int>(modelIndex.row());

    if(index >= (int)(board.boxes.size() * board.boxes[0].size()) || index < 0)
    {
        return (QVariant());
    }

    int x = index/8;
    int y = index%8;
    Spot spot = board.getBox(y,x);
    Piece* piece = spot.getPiece();
    int type = 6;
    bool white = true ;
    if(spot.havePiece())
    {
        type = piece->getType();
        white = piece->isWhite();
    }
    switch (role)
    {
        case Roles::Side     : return white;
        case Roles::Type     : return type;
        case Roles::PositionX: return spot.getX();
        case Roles::PositionY: return spot.getY();
        case Roles::Mark     : return spot.getMark();
    }
    return (QVariant());
}

QHash<int, QByteArray> Game::roleNames(void) const {
    QHash<int, QByteArray> names;
    names.insert(Roles::Side      , "side");
    names.insert(Roles::Type      , "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    names.insert(Roles::Mark      , "mark");
    return (names);
}


