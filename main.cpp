/***********************************************************************
 * File: main.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: main.cpp
***********************************************************************/
#include "Game.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game game;
    //new game
    game.newGame(true);
    QQmlApplicationEngine engine;
    //define game to qml
    engine.rootContext()->setContextProperty("game", &game);
    //connect qml
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
