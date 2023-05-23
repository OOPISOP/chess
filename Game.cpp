/***********************************************************************
 * File: Game.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
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
#include <QDialog>
#include <QProcess>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>


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
    emit resetClockTime();
    board.resetBoard();
    Player p1,p2;

    p1.setWhiteSide(white);
    p2.setWhiteSide(!white);
    this->players.clear();
    this->players.push_back(p1);
    this->players.push_back(p2);
    this->currentTurn = p1;
    this->enPassant = make_pair(-1,-1);
    this->castleRook = make_pair(-1,-1);
    this->fenList.clear();
    this->recordIndex = -1;
    this->effect.setVolume(1.f);
    castleStatusList.clear();
    playerTimeList.clear();
    this->status = ACTIVE;
    recordFEN();
    beginResetModel();
    endResetModel();
}
//Intent:reset all mark
//Pre:no need
//Pos:reset all mark
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

//Intent:see chceck
//Pre:enemy king spot
//Pos:return bool
bool Game::seeCheck(Spot &enemyKingsSpot)
{

    // Initialise.
    int startIndex = (currentTurn.getWhiteSide()) ? 7 : 0;
    int endIndex = (currentTurn.getWhiteSide()) ? -1 : 8;
    int deltaIndex = (currentTurn.getWhiteSide()) ? -1 : 1;

    // Find possible attack to enemy's king.
    for (int row = startIndex; row != endIndex; row += deltaIndex)
    {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot tempSpot = this->board.getBox(row, col);

            if(!tempSpot.havePiece())
            {
                continue;
            }
            Piece *tempPiece = tempSpot.getPiece()->clone();

            // Possible attack found.
            if (tempSpot.havePiece() &&
                (tempPiece->getWhite() == currentTurn.getWhiteSide()) &&
                (canReallyMove(tempSpot, enemyKingsSpot, currentTurn.getWhiteSide())))
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
//Intent:make move simulator
//Pre:temp board ,start and end spot
//Pos:no return just simlator,and change temp baord
void Game::makeMoveSimulator(Board &tempBoard, Spot start, Spot end)
{

    Spot* startBox = &tempBoard.boxes[start.getY()][start.getX()];
    Spot* endBox = &tempBoard.boxes[end.getY()][end.getX()];
    Piece* sourcePiece = startBox->getPiece()->clone();

    pair<int,int> temp = make_pair(castleRook.first,castleRook.second);
    if(isCastle(start.getX(),start.getY(),end.getX(),end.getY()))
    {
        Spot* rookSpot = &tempBoard.boxes[castleRook.second][castleRook.first];
        Piece* rookPiece = rookSpot->getPiece();
        int rookTargetX = (end.getX()-start.getX())>0?end.getX() - 1  : end.getX() + 1;
        Spot* targetSpot = &tempBoard.boxes[end.getY()][rookTargetX];
        targetSpot->setPiece(rookPiece);
        rookSpot->setPiece();
    }
    castleRook.first = temp.first;
    castleRook.second = temp.second;
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
        if(currentTurn.getWhiteSide())
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
        if(currentTurn.getWhiteSide())

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

    if(near->havePiece()&&near->getPiece()->getEnPassant())
    {
        near->setPiece();
    }
    else
    {


        if(this->enPassant.first > 0 && this->enPassant.second > 0)
        {
            Spot* enPassantSpot = &tempBoard.boxes[8 - this->enPassant.second][this->enPassant.first];
            if(enPassantSpot->havePiece())
            {
                Piece* enPassantPiece = enPassantSpot->getPiece()->clone();
                enPassantPiece->setEnPassant(false);
            }
        }
    }
    if(isEnPassant(start.getX(),start.getY(),end.getX(),end.getY()))
    {
        sourcePiece->setEnPassant(true);
    }
}
//Intent:check mate move
//Pre:temp board , white side
//Pos:return bool
bool Game::isCheckmateMove(Board tempBoard, bool isWhite)
{

    Spot* kingsSpot = tempBoard.findKing(isWhite);

    // Initialise.
    int startIndex = (isWhite) ? 0 : 7;
    int endIndex = (isWhite) ? 8 : -1;
    int deltaIndex = (isWhite) ? 1 : -1;

    // Find possible attack from enemy.
    for (int y = startIndex; y != endIndex; y += deltaIndex)
    {
        for (int x = startIndex; x != endIndex; x += deltaIndex)
        {
            // Initialise.
            Spot *tempSpot = tempBoard.getBoxPointer(y, x);

            if (!tempSpot->havePiece())
            {
                continue;
            }

            Piece *tempPiece = tempSpot->getPiece();

            Spot tempSpot2(x, y, tempPiece);

            // Enemy found way to attack King.
            if ((tempPiece->getWhite() != isWhite) &&
                tempPiece->canMove(tempBoard, tempSpot2, *kingsSpot))
            {
                return true;
            }
        }
    }

    return false;
}
//Intent:can really move
//Pre:start end spot and white side
//Pos:return bool
bool Game::canReallyMove(Spot start, Spot end, bool isWhite)
{

    if (start.havePiece()&&start.getPiece()->canMove(board, start, end))
    {
        if(abs(start.getX()-end.getX())==2&&start.getPiece()->getType()==King)
        {
            if(!isCastleCheck(start.getX(),start.getY(),end.getX(),end.getY()))
            {
                return false;
            }
        }
        // Declaration for variables.
        Board tempBoard(board);
        // Simulate next situation.
        makeMoveSimulator(tempBoard, start, end);
        if (!isCheckmateMove(tempBoard, isWhite))
        {
            return true;
        }
    }
    return false;
}

//Intent:see check mate
//Pre:white side
//Pos:return bool
bool Game::seeCheckmate(bool isWhite)
{
    Spot *enemyKingsSpot = this->board.findKing(!isWhite);

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
        Spot tempSpot = this->board.getBox(nextY,nextX);
        // Enemy King has valid move to avoid checkmate.

        if (canReallyMove(*enemyKingsSpot, tempSpot, !isWhite))
        {
            return false;
        }
    }

    // Initialise index variables.
    int startIndex = (isWhite) ? 0 : 7;
    int endIndex = (isWhite) ? 8 : -1;
    int deltaIndex = (isWhite) ? 1 : -1;

    // No checkmate when enemy's piece can block checkmate.
    for (int row = startIndex; row != endIndex; row += deltaIndex)
    {
        for (int col = startIndex; col != endIndex; col += deltaIndex)
        {
            // Initialise.
            Spot enemySpot = board.getBox(row, col);

            if(!enemySpot.havePiece())
            {
                continue;
            }

            Piece *enemyPiece = enemySpot.getPiece();

            // Enemy found.
            if (enemySpot.havePiece() &&
                (enemyPiece->getWhite() != isWhite))
            {
                // See every move can enemy made.
                for (int row2 = startIndex; row2 != endIndex; row2 += deltaIndex)
                {
                    for (int col2 = startIndex; col2 != endIndex; col2 += deltaIndex)
                    {
                        // Initialise.
                        Spot tempSpot = board.getBox(row2, col2);

                        // Found way to block checkmate.
                        if (canReallyMove(enemySpot, tempSpot, !isWhite))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
//Intent:time up
//Pre:white
//Pos:set time up and show
void Game::timeUp(bool white)
{

    string message = "Time Up! " ;
    message += ((white) ? "BLACK_WIN/WHITE_LOSE" : "WHITE_WIN/BLACK_LOSE");
    resetAllMark();
    beginResetModel();
    endResetModel();
    // PLAY RESIGN SOUND.
    playChessSound(resignSound);
    showStatusMessage(message);
}
//Intent:surrender
//Pre:white
//Pos:surrend and show
void Game::surrender(int white)
{
    emit clockStop();
    string message = "Surrender! " ;
    message += ((white) ? "BLACK_WIN/WHITE_LOSE" : "WHITE_WIN/BLACK_LOSE");
    resetAllMark();
    beginResetModel();
    endResetModel();
    // PLAY RESIGN SOUND.
    playChessSound(resignSound);
    showStatusMessage(message);
}


//Intent:show next move
//Pre:x y
//Pos:show next move
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

    if(sourcePiece->getWhite() != currentTurn.getWhiteSide())
    {
        cout<<"not your turn"<<endl;
        return;
    }

    for(int row=0;row<8;row++)
    {
        for(int col=0;col<8;col++)
        {
            Spot* endBox = &this->board.boxes[row][col];

            if(canReallyMove(*startBox,*endBox, currentTurn.getWhiteSide()))
            {
                endBox->setMark(true);
            }
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


    if(sourcePiece->getWhite() != currentTurn.getWhiteSide())

    {
        cout<<"not your turn"<<endl;
        return false;
    }


    if(!canReallyMove(*startBox,*endBox, currentTurn.getWhiteSide()))
    {
        cout<<"can't move"<<endl;
        return false;
    }

    int finalSound = -1;


    if(isCastle(startX,startY,endX,endY))
    {
        Spot* rookSpot = &this->board.boxes[castleRook.second][castleRook.first];
        Piece* rookPiece = rookSpot->getPiece();
        int rookTargetX = (endX-startX)>0?endX - 1  : endX + 1;
        Spot* targetSpot = &this->board.boxes[endY][rookTargetX];
        targetSpot->setPiece(rookPiece);
        rookSpot->setPiece();
        castleRook = make_pair(-1,-1);


        // PLAY CASTLING SOUND.
        finalSound = castleSound;
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
        if(currentTurn.getWhiteSide())
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

        if(currentTurn.getWhiteSide())

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

    Spot* near = &this->board.boxes[startY][endX];

    if(near->havePiece()&&near->getPiece()->getEnPassant())
    {
        near->setPiece();

        // PLAY ENPASSANT SOUND.
        finalSound = passantSound;

    }
    else
    {
        if(this->enPassant.first > 0 && this->enPassant.second > 0)
        {
            cout<<"bbb"<<endl;
            Spot* enPassantSpot = &this->board.boxes[8 - this->enPassant.second][this->enPassant.first];
            if(enPassantSpot->havePiece())
            {
                Piece* enPassantPiece = enPassantSpot->getPiece();
                enPassantPiece->setEnPassant(false);
            }
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

    resetAllMark();
    beginResetModel();
    endResetModel();

    if(!gameStatusUpdate(finalSound))
    {
        return false;
    }


    if (sourcePiece->getType() == Pawn &&(endY==0 || endY == 7) )
    {
        //promotion
        emit showPopup(endX,endY,sourcePiece->getWhite());
        return true;
    }

    if(this->currentTurn == players[0])
    {
        this->currentTurn = players[1];
    }
    else
    {
        this->currentTurn = players[0];
    }
    //emit clockStart(currentTurn.getWhiteSide());
    if (finalSound == -1)
    {
        int moveSound = (currentTurn == players[1]) ? 1 : 0;
        playChessSound(moveSound);
    }
    else
    {
        playChessSound(finalSound);
    }
    recordFEN();
    return true;
}

//Intent:game status update
//Pre:final sound
//Pos:return bool and change final sound
bool Game::gameStatusUpdate(int& finalSound)
{
    bool statusCheck = seeCheck(*this->board.findKing(!currentTurn.getWhiteSide()));
    bool whoCheckmate = 0;
    if (status == RESIGNATION)
    {
        string message = (currentTurn.getWhiteSide()) ? "BLACK_WIN/WHITE_LOSE" : "WHITE_WIN/BLACK_LOSE";
        cout << message << endl;
        resetAllMark();
        // PLAY RESIGN SOUND.
        playChessSound(resignSound);
        showStatusMessage(message);
        beginResetModel();
        endResetModel();
        return false;
    }
    else if (seeCheckmate(currentTurn.getWhiteSide()))
    {
        whoCheckmate = currentTurn.getWhiteSide();
        status = CHECKMATE;
    }
    else if (seeCheckmate(!currentTurn.getWhiteSide()))
    {
        whoCheckmate = !currentTurn.getWhiteSide();

        status = CHECKMATE;
    }
    else if (statusCheck)
    {
        // PLAY CHECK SOUND.

        finalSound = checkSound;

    }
    if (status == CHECKMATE)
    {
        if (statusCheck)
        {
            // PLAY CHECKMATE SOUND.
            playChessSound(checkmateSound);
            string message = (currentTurn.getWhiteSide()) ? "WHITE_WIN/BLACK_LOSE" : "BLACK_WIN/WHITE_LOSE";
            cout << message << endl;
            int soundType = (whoCheckmate) ? winSound : loseSound;
            resetAllMark();
            // PLAY WIN OR LOSE SOUND.
            playChessSound(soundType);
            showStatusMessage(message);
            beginResetModel();
            endResetModel();
            return false;
        }
        else
        {
            status = STALEMATE;
            cout << "DRAW" << endl;
            resetAllMark();
            // PLAY DRAW SOUND.
            playChessSound(drawSound);
            showStatusMessage("DRAW");
            beginResetModel();
            endResetModel();
            return false;
        }
    }

    return true;
}
//Intent:show status message
//Pre:message
//Pos:show status message
void Game::showStatusMessage(string message)
{
    QDialog dialog;
    //if quit the dialog will quit the game
    QObject::connect(&dialog, &QDialog::finished, qApp, &QApplication::quit);
    QVBoxLayout layout(&dialog);
    QHBoxLayout buttonLayout;
    QLabel label(QString::fromStdString(message), &dialog);
    layout.addWidget(&label);
    //replay button to replay the game
    QPushButton okButton("Replay", &dialog);
    buttonLayout.addWidget(&okButton);
    // QObject::connect(&okButton, &QPushButton::clicked, this, &Game::replayGame);
    // 連接按鈕的 clicked() 信號到一個槽函式
    QObject::connect(&okButton, &QPushButton::clicked, [&dialog, this]() {
        // 關閉 QDialog
        dialog.hide();
        // 執行您想要執行的函式
        newGame(true);
    });
    //quit button to quit the game
    QPushButton cancelButton("Quit", &dialog);
    buttonLayout.addWidget(&cancelButton);
    QObject::connect(&cancelButton, &QPushButton::clicked, qApp, &QApplication::quit);
    layout.addLayout(&buttonLayout);
    dialog.exec();
}

//Intent:play chess sound effect
//Pre:sound type
//Pos:play chess sound effect
void Game::playChessSound(int soundType)
{
    QString soundSource;

    switch (soundType)
    {
    case move1Sound:
        soundSource = p1ChessSound;
        break;
    case move2Sound:
        soundSource = p2ChessSound;
        break;
    case checkSound:
        soundSource = checkChessSound;
        break;
    case checkmateSound:
        soundSource = checkmateChessSound;
        break;
    case drawSound:
        soundSource = drawChessSound;
        break;
    case winSound:
        soundSource = winChessSound;
        break;
    case loseSound:
        soundSource = loseChessSound;
        break;
    case resignSound:
        soundSource = resignChessSound;
        break;
    case passantSound:
        soundSource = passantChessSound;
        break;
    case castleSound:
        soundSource = castleChessSound;
        break;
    }

    effect.setSource(QUrl::fromLocalFile(soundSource));
    effect.play();
}
//Intent:castle
//Pre:startX startY endX endY
//Pos::return bool
bool Game::isCastle(int startX,int startY,int endX,int endY)
{
    Spot* startBox = &this->board.boxes[startY][startX];
    Piece* startPiece = startBox->getPiece();
    if(startPiece->getType()!=King||(startPiece->getWhite()&&board.whiteKingMoved)||((!startPiece->getWhite()&&board.blackKingMoved)))
    {
        return false;
    }
    int deltaY = endY - startY;
    int deltaX = endX - startX;
    if(deltaY!=0||abs(deltaX)<2)
    {
        return false;
    }
    if(!isCastleCheck(startX,startY,endX,endY))
    {
        return false;
    }
    castleRook = make_pair((deltaX>0)?7:0,endY);
    return true;
}

bool Game::isCastleCheck(int startX,int startY,int endX,int endY)
{
    Spot* startBox = &this->board.boxes[startY][startX];
    Piece* startPiece = startBox->getPiece();
    if(startPiece->getType()!=King||(startPiece->getWhite()&&board.whiteKingMoved)||((!startPiece->getWhite()&&board.blackKingMoved)))
    {
        return false;
    }
    int deltaY = endY - startY;
    int deltaX = endX - startX;
    if(deltaY!=0||abs(deltaX)<2)
    {
        return false;
    }

    for(int i=startX+((deltaX>0)?1:-1);i!=endX;i+=(deltaX>0)?1:-1)
    {
        Spot* endBox = &this->board.boxes[startY][i];
        if(!canReallyMove(*startBox,*endBox,startBox->getPiece()->getWhite()))
        {
            return false;
        }
    }
    return true;
}
//Intent:en passant
//Pre:startX startY endX endY
//Pos:return bool
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
    bool white = piece->getWhite();
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
    int finalSound = -1;
    gameStatusUpdate(finalSound);
    if(this->currentTurn == players[0])
    {
        this->currentTurn = players[1];
    }
    else
    {
        this->currentTurn = players[0];
    }
    if (finalSound == -1)
    {
        int moveSound = (currentTurn == players[1]) ? 1 : 0;
        playChessSound(moveSound);
    }
    else
    {
        playChessSound(finalSound);
    }
    //emit clockStart(currentTurn.getWhiteSide());
    recordFEN();
}
//Intent:record FEN
//Pre:fen
//Pos:record fen
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
            if(PIECE->getWhite())
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
    if(currentTurn.getWhiteSide())
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
    emit getClockTime();
    emit clockStart(currentTurn.getWhiteSide());
    this->fenList.push_back(fen);
    this->castleStatusList.push_back(castleStatus);
    cout<<fen<<endl;
    this->recordIndex++;
}
void Game::updateClockTime(int timeOne,int timeTwo)
{
    pair<int,int> time = make_pair(timeOne,timeTwo);
    playerTimeList.push_back(time);
}
//Intent:set fen
//Pre:fen
//Pos:set fen and return bool
bool Game::setFEN(QString fen)
{
    KingAndRookStatus status;
    if(fen.isEmpty()||!setGame(fen.toStdString(),status))
    {
        return false;
    }
    recordFEN();
    emit resetClockTime();
    return true;
}
//Intent:set board from fen
//Pre:fen
//Pos:set bard from fen
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
//Intent:upadaste king rook
//Pre:fen
//Posupdate king rook
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
//Intent:set game
//Pre:fen status
//Pos:return bool and set game
bool Game::setGame(string fen,KingAndRookStatus status)
{
    vector<std::string> parts;
    stringstream ss(fen);
    string part;
    while (getline(ss, part, ' '))
    {
        parts.push_back(part);
    }
    if(parts.size()<4)
    {
        return false;
    }
    setBoardFromFEN(parts[0]);
    Player p1,p2;
    p1.setWhiteSide(true);
    p2.setWhiteSide(false);
    this->players.push_back(p1);
    this->players.push_back(p2);
    if(parts[1].empty()||(parts[1]!="w"&&parts[1]!="b"))
    {
        setGame(fenList[recordIndex],castleStatusList[recordIndex]);
        return false;
    }
    currentTurn = (parts[1] == "w") ? p1 : p2;
    if(parts[2].empty()||parts[2]==" "||parts[2] == "")
    {
        return false;
    }
    updateKingRook(parts[2]);
    if(recordIndex>=0)
    {
        setCastleFromFEN(status);
    }
    if(parts[3].empty()||parts[3] == " "||parts[3]=="")
    {
        cout<<"en Passant error pos"<<endl;
        return false;
    }
    if (parts[3] != "-")
    {
        int file = parts[3][0] - 'a';
        int rank = 8 - (parts[3][1] - '0') ;
        this->enPassant = make_pair(file, rank);
        if(file>7||file<0||rank>7||rank<0)
        {
            setGame(fenList[recordIndex],castleStatusList[recordIndex]);
            cout<<"en Passant error pos"<<endl;
            return false;
        }
        Spot* spot = &this->board.boxes[rank][file];
        Piece* piece = spot->getPiece();
        piece->setEnPassant(true);
    }
    beginResetModel();
    endResetModel();
    return true;
}
//Intent:set castle from fen
//Pre:status
//Pos:set castle from fen
void Game::setCastleFromFEN(KingAndRookStatus status)
{
    board.whiteKingMoved = status.whiteKingMoved;
    board.whiteLeftRookMoved = status.whiteLeftRookMoved;
    board.whiteRightRookMoved = status.whiteRightRookMoved;
    board.blackKingMoved = status.blackKingMoved;
    board.blackLeftRookMoved = status.blackLeftRookMoved;
    board.blackRightRookMoved = status.blackRightRookMoved;
}
//Intent:redo
//Pre:record index and fen list
//Pos:redo
void Game::redo()
{
    if(recordIndex >= (int)fenList.size() - 1)
    {
        return ;
    }
    recordIndex++;
    cout<<fenList[recordIndex]<<endl;
    if(playerTimeList.size()>recordIndex)
    {
       emit setClockTime(playerTimeList[recordIndex].first,playerTimeList[recordIndex].second);
    }
    setGame(fenList[recordIndex],castleStatusList[recordIndex]);
    emit clockStart(currentTurn.getWhiteSide());
}
//Intent:undo
//Pre:record index and fen list
//Pos:undo
void Game::undo()
{
    if(recordIndex <= 0)
    {
        return ;
    }
    recordIndex--;
    cout<<fenList[recordIndex]<<endl;
    if(!playerTimeList.empty())
    {
         emit setClockTime(playerTimeList[recordIndex].first,playerTimeList[recordIndex].second);
    }
    setGame(fenList[recordIndex],castleStatusList[recordIndex]);
    emit clockStart(currentTurn.getWhiteSide());
}
//model row count
int Game::rowCount(const QModelIndex & ) const {
    return (board.boxes.size()*board.boxes[0].size());
}
//model data
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
        white = piece->getWhite();
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
//model role name
QHash<int, QByteArray> Game::roleNames(void) const {
    QHash<int, QByteArray> names;
    names.insert(Roles::Side      , "side");
    names.insert(Roles::Type      , "type");
    names.insert(Roles::PositionX , "positionX");
    names.insert(Roles::PositionY , "positionY");
    names.insert(Roles::Mark      , "mark");
    return (names);
}
