#ifndef GAME_H
#define GAME_H

<<<<<<< HEAD
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

=======
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
>>>>>>> 512f4a0 (f)

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
<<<<<<< HEAD
        kingThreatSound,
        drawSound,
        winSound,
        loseSound,
        resignSound
    };


=======
        drawSound,
        winSound,
        loseSound,
        resignSound,
        passantSound,
        castleSound
    };

>>>>>>> 512f4a0 (f)
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
<<<<<<< HEAD
    Q_INVOKABLE bool makeMove(int startX,int startY,int endX,int endY);

    Spot FindKing(Board board, bool isWhite);
    bool seeCheck(Spot enemyKingsSpot);
=======
    void resetAllMark();

    bool seeCheck(Spot &enemyKingsSpot);
>>>>>>> 512f4a0 (f)
    bool seeCheckmate(bool isWhite);
    bool isCheckmateMove(Board tempBoard, bool isWhite);
    bool canReallyMove(Spot start, Spot end, bool isWhite);
    void makeMoveSimulator(Board &tempBoard, Spot start, Spot end);

<<<<<<< HEAD

    Q_INVOKABLE void showNextMove(int x,int y);
    void resetAllMark();
=======
    Q_INVOKABLE void showNextMove(int x,int y);
    Q_INVOKABLE bool makeMove(int startX,int startY,int endX,int endY);

>>>>>>> 512f4a0 (f)
    Q_INVOKABLE void promotion(int x,int y,int i);
    Q_INVOKABLE bool setFEN(QString fen);
    void recordFEN();
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    void setGame(string fen,KingAndRookStatus status);
    void setBoardFromFEN(string fen);
    bool isEnPassant(int startX,int startY,int endX,int endY);
<<<<<<< HEAD

=======
>>>>>>> 512f4a0 (f)
    void playChessSound(int soundType);
    bool isCastle(int startX,int startY,int endX,int endY);
    void setCastleFromFEN(KingAndRookStatus status);
    void updateKingRook(string fen);
    void showStatusMessage(string message);
<<<<<<< HEAD


=======
    bool isCastleCheck(int startX,int startY,int endX,int endY);
>>>>>>> 512f4a0 (f)

protected:
    //board row count
    int rowCount(const QModelIndex & parent) const override;
    //board data set
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const override;
    //set role name to qml
    QHash<int, QByteArray> roleNames() const override;
<<<<<<< HEAD
signals:
 void showPopup(int x,int y,bool white);

=======

signals:
    void showPopup(int x,int y,bool white);
>>>>>>> 512f4a0 (f)

private:
    vector<Player> players;
    Board board;
    Player currentTurn;
<<<<<<< HEAD

    GameStatus status = ACTIVE;

    pair<int,int> enPassant;
    vector<string> fenList;
    int recordIndex;
    QString p1ChessSound = ":/sounds/move1.wav";
    QString p2ChessSound = ":/sounds/move2.wav";

    QString checkChessSound = ":/sounds/check.wav";
    QString checkmateChessSound = ":/sounds/checkmate.wav";
    QString kingThreatChessSound = ":/sounds/kingThreat.wav";
=======
    GameStatus status = ACTIVE;

    pair<int,int> enPassant;
    pair<int,int> castleRook;
    vector<KingAndRookStatus> castleStatusList;
    vector<string> fenList;
    int recordIndex;

    QString p1ChessSound = ":/sounds/move1.wav";
    QString p2ChessSound = ":/sounds/move2.wav";
    QString checkChessSound = ":/sounds/check.wav";
    QString checkmateChessSound = ":/sounds/checkmate.wav";
>>>>>>> 512f4a0 (f)
    QString drawChessSound = ":/sounds/draw.wav";
    QString winChessSound = ":/sounds/win.wav";
    QString loseChessSound = ":/sounds/lose.wav";
    QString resignChessSound = ":/sounds/resign.wav";
<<<<<<< HEAD

    //音效播放器
    QSoundEffect effect;
    pair<int,int> castleRook;
    vector<KingAndRookStatus> castleStatusList;

};
=======
    QString passantChessSound = ":/sounds/passant.wav";
    QString castleChessSound = ":/sounds/castle.wav";

    //音效播放器
    QSoundEffect effect;
};

>>>>>>> 512f4a0 (f)
#endif // GAME_H
