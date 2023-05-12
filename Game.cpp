/***********************************************************************
 * File: Game.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: Brendon
 * Update Date: 2023/05/10
 * Description: Game
***********************************************************************/
#include "Game.h"
#include "Spot.h"
#include <queue>

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

            Spot* endBox = &this->board.boxes[nextY][nextX];
            if(nextX>7||nextX<0||nextY>7||nextY<0)continue;
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
        startBox->setPiece();
        endBox->setPiece(sourcePiece);
    }
    else
    {
        Piece* targetPiece = endBox->getPiece();
        startBox->setPiece(targetPiece);
        endBox->setPiece(sourcePiece);
    }
    if (sourcePiece->isEnPassant())
    {

    }
    else if (sourcePiece->isCastling())
    {

    }
    else
    {
        startBox->setPiece();
        endBox->setPiece(sourcePiece);

        if (sourcePiece->isPromoting())
        {
            // {}{}{{}{}Need Piece selecting window{}{{{}{}{}
            // {}{}{}{}} And change(setPiece?) endBox's Piece to selected one.
        }
    }

    if(this->currentTurn == players[0])
    {
        this->currentTurn = players[1];
    }
    else
    {
        this->currentTurn = players[0];
    }
    resetAllMark();
    emit dataChanged(index(0),index(63));
    return true;
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


