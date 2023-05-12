#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
# include <QAbstractListModel>
# include <QDebug>
# include <QList>
# include <QByteArray>
# include <QHash>
#include <vector>
#include <iostream>

#include "Player.h"
#include "Board.h"
#include "Spot.h"
using namespace std;


class Game : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    ~Game();

    enum GameStatus
    {
        ACTIVE,
        BLACK_WIN,
        FOREIT,
        STALEMATE,
        RESIGNATTON
    };

    enum Roles
    {
        Side = Qt::UserRole,
        Type,
        PositionX,
        PositionY,
        Mark,
    };

    enum Types {
        Pawn,
        Rook,
        Bishop,
        Knight,
        Queen,
        King
    };

    Q_INVOKABLE void newGame();
    Q_INVOKABLE bool makeMove(int startX,int startY,int endX,int endY);
    Q_INVOKABLE void showNextMove(int x,int y);
    void resetAllMark();


protected:
    //board row count
    int rowCount(const QModelIndex & parent) const override;
    //board data set
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    //set role name to qml
    QHash<int, QByteArray> roleNames() const override;
private:
    vector<Player> players;
    Board board;
    Player currentTurn;
    GameStatus status;
};
#endif // GAME_H
