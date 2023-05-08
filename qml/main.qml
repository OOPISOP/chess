import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ApplicationWindow
{
    id: root
    title: qsTr("Chess")
    visible: true
    minimumWidth: 8 * squareSize
    minimumHeight: 8 * squareSize

    property int squareSize: 80

    property var images: [
        [
            {'imgPath' : "/images/white_pawn.svg"},
            {'imgPath' : "/images/white_rook.svg"},
            {'imgPath' : "/images/white_bishop.svg"},
            {'imgPath' : "/images/white_knight.svg"},
            {'imgPath' : "/images/white_queen.svg"},
            {'imgPath' : "/images/white_king.svg"}
        ],

        [
            {'imgPath' : "/images/black_pawn.svg"},
            {'imgPath' : "/images/black_rook.svg"},
            {'imgPath' : "/images/black_bishop.svg"},
            {'imgPath' : "/images/black_knight.svg"},
            {'imgPath' : "/images/black_queen.svg"},
            {'imgPath' : "/images/black_king.svg"}
        ]
    ]

    Component {
        // First screen
        id: gameBoard
        Item {
            Image {
                id: board
                source: "/images/chess_board.jpg"
                height: 8 * squareSize
                width: 8 * squareSize
            }
        }
    }

    Component {
        id: chessPlacement
        Item {
            Repeater {
                model: game
                Image {
                    height: squareSize
                    width : squareSize

                    x: squareSize * positionX
                    y: squareSize * positionY

                    source: images[(side == true) ? 0 : 1][type].imgPath

                    MouseArea {
                        anchors.fill: parent
                        drag.target: parent
                        property int startX: 0
                        property int startY: 0
                        onPressed: {
                            console.log("On press: ", parent.x, parent.y);
//                            startX = parent.x;
//                            startY = parent.y;
                        }
                        onReleased: {
                            var  fromX = startX / squareSize;
                            var fromY = startY / squareSize;
                            var toX   = (parent.x + mouseX) / squareSize;
                            var toY   = (parent.y + mouseY) / squareSize;
//                            if (!logic.move(fromX, fromY, toX, toY))
//                            {
//                                parent.x = startX;
//                                parent.y = startY;
//                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: mainScreen
        Item {
            Loader {sourceComponent: gameBoard}
            Loader {sourceComponent: chessPlacement}
//            Loader {sourceComponent: buttonNewGame}
//            Loader {sourceComponent: buttonLoadGame}
        }
    }
    StackView {
        id: screen
        anchors.fill: parent
        initialItem: mainScreen
    }
}
