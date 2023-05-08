#include "Game.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game game;
    //new game
    game.newGame();
    QQmlApplicationEngine engine;
    //define game to qml
    engine.rootContext()->setContextProperty("game", &game);
    //connect qml
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
