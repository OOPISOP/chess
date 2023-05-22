/***********************************************************************
 * File: Game.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Game define
***********************************************************************/
#ifndef GAME_H
#define GAME_H

#define _HAS_STD_BYTE 0

#include "QtMultimedia/qsoundeffect.h"
#include <QMainWindow>
#include <QAbstractListModel>
#include <QDebug>
#include <QList>
#include <QByteArray>
#include <QHash>
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
    //game status
    enum GameStatus
    {
        ACTIVE,
        CHECKMATE,
        STALEMATE,
        RESIGNATION,
        FOREIT
    };
    //game model roles
    enum Roles
    {
        Side = Qt::UserRole,
        Type,
        PositionX,
        PositionY,
        Mark,
    };
    //piece types
    enum Types {
        Pawn,
        Rook,
        Bishop,
        Knight,
        Queen,
        King
    };
    //sound effect types
    enum SoundTypes
    {
        move1Sound,
        move2Sound,
        checkSound,
        checkmateSound,
        drawSound,
        winSound,
        loseSound,
        resignSound,
        passantSound,
        castleSound
    };
    //castle status
    struct  KingAndRookStatus
    {
        bool whiteKingMoved = false;
        bool whiteLeftRookMoved = false;
        bool whiteRightRookMoved = false;
        bool blackKingMoved = false;
        bool blackLeftRookMoved = false;
        bool blackRightRookMoved = false;
    };

    Q_INVOKABLE void newGame(bool white);//new game
    void resetAllMark();//reset mark

    bool seeCheck(Spot &enemyKingsSpot);//see check
    bool seeCheckmate(bool isWhite);//see check mate
    bool isCheckmateMove(Board tempBoard, bool isWhite);//is check mate move
    bool canReallyMove(Spot start, Spot end, bool isWhite);//can really move
    void makeMoveSimulator(Board &tempBoard, Spot start, Spot end);//move simular
    Q_INVOKABLE void showNextMove(int x,int y);//show next move
    Q_INVOKABLE bool makeMove(int startX,int startY,int endX,int endY);//make move

    Q_INVOKABLE void promotion(int x,int y,int i);//promotion
    Q_INVOKABLE bool setFEN(QString fen);//set fen
    void recordFEN();//fen record
    Q_INVOKABLE void undo();//undo
    Q_INVOKABLE void redo();//redo
    bool setGame(string fen,KingAndRookStatus status);//set game
    void setBoardFromFEN(string fen);//set board from fen
    bool isEnPassant(int startX,int startY,int endX,int endY);//en passant
    void playChessSound(int soundType);//sound effect play
    bool isCastle(int startX,int startY,int endX,int endY);//castle
    void setCastleFromFEN(KingAndRookStatus status);//fen castle set
    void updateKingRook(string fen);//update king rook
    void showStatusMessage(string message);//show status message
    bool isCastleCheck(int startX,int startY,int endX,int endY);//castle check
    bool gameStatusUpdate(int &finalSound);//game status update
    Q_INVOKABLE void timeUp(bool white);//time up
    Q_INVOKABLE void updateClockTime(int timeOne,int timeTwo);

protected:
    //board row count
    int rowCount(const QModelIndex & parent) const override;
    //board data set
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    //set role name to qml
    QHash<int, QByteArray> roleNames() const override;

signals:
    void showPopup(int x,int y,bool white);//show promotion popup
    void clockStart(bool white);//clock start
    void resetClockTime();//reset clock time
    int getClockTime();
    void setClockTime(int timeOne,int timeTwo);

private:
    vector<Player> players;
    Board board;
    Player currentTurn;
    GameStatus status = ACTIVE;

    pair<int,int> enPassant;
    pair<int,int> castleRook;
    vector<KingAndRookStatus> castleStatusList;
    vector<string> fenList;
    int recordIndex;
    vector<pair<int,int>>playerTimeList;

    QString p1ChessSound = ":/sounds/move1.wav";
    QString p2ChessSound = ":/sounds/move2.wav";
    QString checkChessSound = ":/sounds/check.wav";
    QString checkmateChessSound = ":/sounds/checkmate.wav";
    QString drawChessSound = ":/sounds/draw.wav";
    QString winChessSound = ":/sounds/win.wav";
    QString loseChessSound = ":/sounds/lose.wav";
    QString resignChessSound = ":/sounds/resign.wav";
    QString passantChessSound = ":/sounds/passant.wav";
    QString castleChessSound = ":/sounds/castle.wav";

    //音效播放器
    QSoundEffect effect;
};

#endif // GAME_H
