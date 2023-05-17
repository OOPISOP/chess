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
        CHECKMATE,
        STALEMATE,
        RESIGNATION,
        FOREIT
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

    enum SoundTypes
    {
        move1Sound,
        move2Sound,
        checkSound,
        checkmateSound,
        kingThreatSound,
        drawSound,
        winSound,
        loseSound,
        resignSound
    };

    struct  KingAndRookStatus
    {
        bool whiteKingMoved = false;
        bool whiteLeftRookMoved = false;
        bool whiteRightRookMoved = false;
        bool blackKingMoved = false;
        bool blackLeftRookMoved = false;
        bool blackRightRookMoved = false;
    };

    Q_INVOKABLE void newGame(bool white);
    Q_INVOKABLE bool makeMove(int startX,int startY,int endX,int endY);
    Spot FindKing(Board board, bool isWhite);
    bool seeCheck(Spot enemyKingsSpot);
    bool seeCheckmate(bool isWhite);
    bool isCheckmateMove(Board tempBoard, bool isWhite);
    bool canReallyMove(Spot start, Spot end, bool isWhite);
    void makeMoveSimulator(Board &tempBoard, Spot start, Spot end);

    Q_INVOKABLE void showNextMove(int x,int y);
    void resetAllMark();
    Q_INVOKABLE void promotion(int x,int y,int i);
    Q_INVOKABLE bool setFEN(QString fen);
    void recordFEN();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    void setGame(string fen,KingAndRookStatus status);
    void setBoardFromFEN(string fen);
    bool isEnPassant(int startX,int startY,int endX,int endY);
    void playChessSound(int soundType);
    bool isCastle(int startX,int startY,int endX,int endY);
    void setCastleFromFEN(KingAndRookStatus status);
    void updateKingRook(string fen);


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
    QString checkChessSound = ":/sounds/check.mp3";
    QString checkmateChessSound = ":/sounds/checkmate.mp3";
    QString kingThreatChessSound = ":/sounds/kingThreat.mp3";
    QString drawChessSound = ":/sounds/draw.mp3";
    QString winChessSound = ":/sounds/win.mp3";
    QString loseChessSound = ":/sounds/lose.mp3";
    QString resignChessSound = ":/sounds/resign.mp3";
    //音效播放器
    QSoundEffect effect;
    pair<int,int> castleRook;
    vector<KingAndRookStatus> castleStatusList;

};
#endif // GAME_H
