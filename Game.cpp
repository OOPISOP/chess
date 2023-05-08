#include "Game.h"
#include "Spot.h"
Game::Game(QObject *parent) : QAbstractListModel(parent)
{

}

Game::~Game()
{
}

void Game::newGame()
{
    board.resetBoard();
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

    if(index >= (board.boxes.size()*board.boxes[0].size()) || index<0)
    {
        return (QVariant());
    }
    //Figure      &figure = impl->figures[index];
    int y = index/8;
    int x = index%8;
    Spot spot = board.getBox(x,y);
    Piece piece = spot.getPiece();
    int type;
    type = piece.getType();
    switch (role)
    {
        case Roles::Side     : return piece.isWhite();
        case Roles::Type     : return type;
        case Roles::PositionX: return spot.getX();
        case Roles::PositionY: return spot.getY();
    }

    return (QVariant());
}

QHash<int, QByteArray> Game::roleNames(void) const {
    QHash<int, QByteArray> names;
    names.insert(Roles::Side      , "side");
    names.insert(Roles::Type      , "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    return (names);
}
