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
    Player p1,p2;
    p1.setSide(true);
    p2.setSide(false);
    this->players.push_back(p1);
    this->players.push_back(p2);
    this->currentTurn = p1;
    if(p2.isWhiteSide())
    {
        this->currentTurn = p2;
    }
    this->enPassant = make_pair(-1,-1);
    this->fenList.clear();
    this->recordIndex = -1;

}

Game::~Game()
{
    this->players.clear();
}
//Intent:creat  the new Game
//Pre:p1 p2 is Player represent player,and push back to players ,represent have two player,and set the current player
//Pos:set two player and current turn
void Game::newGame()
{
    board.resetBoard();
    Player p1,p2;
    p1.setSide(true);
    p2.setSide(false);
    this->players.push_back(p1);
    this->players.push_back(p2);
    this->currentTurn = p1;
    if(p2.isWhiteSide())
    {
        this->currentTurn = p2;
    }
    this->enPassant = make_pair(-1,-1);
    this->fenList.clear();
    this->recordIndex = -1;
    this->effect.setVolume(1.f);
    recordFEN();
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
    queue<bool>flag;
    vector<vector<bool>> vis(8,vector<bool>(8,false));
    que.push(pair<int, int>(x, y));
    flag.push(false);
    while(!que.empty())
    {
        int x = que.front().first;
        int y = que.front().second;
        bool v = flag.front();
        que.pop();
        flag.pop();
        for(int i=0;i<8;i++)
        {
            int nextX = x + dir[i][0];
            int nextY = y + dir[i][1];
            if(nextX>7||nextX<0||nextY>7||nextY<0)continue;
            Spot* endBox = &this->board.boxes[nextY][nextX];
            if(sourcePiece->canMove(board,*startBox,*endBox) && !vis[nextX][nextY] && !v)
            {
                endBox->setMark(true);
                que.push(pair<int, int>(nextX, nextY));
                if(endBox->havePiece())
                {
                    flag.push(true);
                }
                else
                {
                    flag.push(false);
                }
            }
            vis[nextX][nextY] = true;
        }
    }
   emit dataChanged(index(0),index(63));
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
    if(!sourcePiece->canMove(board,*startBox,*endBox))
    {
        cout<<"can't move"<<endl;
        return false;
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

    if (sourcePiece->isCastling())
    {

    }

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


void Game::setFEN(string fen)
{

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
    fen += " - ";
    if(this->enPassant.first < 0 || this->enPassant.second < 0)
    {
        fen += "- ";
    }
    else
    {
        fen += 'a' + this->enPassant.first;
        fen += '0' + this->enPassant.second;
    }
    cout<<fen<<endl;
    this->fenList.push_back(fen);
    this->recordIndex++;
    cout<<"index:"<<recordIndex<<endl;
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

void Game::setGame(string fen)
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
        cout<<"en "<<file<<" "<<rank<<endl;
        piece->setEnPassant(true);
    }
    beginResetModel();
    endResetModel();
}

void Game::redo()
{
    if(recordIndex >= fenList.size() - 1)
    {
        return ;
    }
    recordIndex++;
    cout<<fenList[recordIndex]<<endl;
    setGame(fenList[recordIndex]);
}

void Game::undo()
{
    if(recordIndex <= 0)
    {
        return ;
    }
    recordIndex--;
    cout<<"index:"<<recordIndex<<endl;
    cout<<"index:"<<fenList[recordIndex]<<endl;
    setGame(fenList[recordIndex]);
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

    if(index >= (board.boxes.size() * board.boxes[0].size()) || index < 0)
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


