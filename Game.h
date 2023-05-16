#ifndef GAME_H
#define GAME_H

#include "QtMultimedia/qsoundeffect.h"
#define _HAS_STD_BYTE 0

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
    Q_INVOKABLE void promotion(int x,int y,int i);
    void setFEN(string fen);
    void recordFEN();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    void setGame(string fen);
    void setBoardFromFEN(string fen);
    bool isEnPassant(int startX,int startY,int endX,int endY);
    void playChessSound();

protected:
    //board row count
    int rowCount(const QModelIndex & parent) const override;
    //board data set
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    //set role name to qml
    QHash<int, QByteArray> roleNames() const override;
signals:
 void showPopup(int x,int y,bool white);


private:
    vector<Player> players;
    Board board;
    Player currentTurn;
    GameStatus status;
    pair<int,int> enPassant;
    vector<string> fenList;
    int recordIndex;
    QString p1ChessSound = ":/sounds/move1.wav";
    QString p2ChessSound = ":/sounds/move2.wav";
    //音效播放器
    QSoundEffect effect;
};
#endif // GAME_H
