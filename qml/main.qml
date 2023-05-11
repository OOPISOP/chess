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
            "/images/white_pawn.svg",
            "/images/white_rook.svg",
            "/images/white_bishop.svg",
            "/images/white_knight.svg",
            "/images/white_queen.svg",
            "/images/white_king.svg",
            ""
        ],

        [
            "/images/black_pawn.svg",
            "/images/black_rook.svg",
            "/images/black_bishop.svg",
            "/images/black_knight.svg",
            "/images/black_queen.svg",
            "/images/black_king.svg",
            ""
        ],

        [
            "/images/square.png",
            ""
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

    Component
    {
        id: chessPlacement
        Item {
            Repeater
            {
                model: game
                Item
                {
                    Image
                    {
                        height: squareSize
                        width : squareSize

                        x: squareSize * positionX
                        y: squareSize * positionY
                        z: 0

                        source: images[(side == true) ? 0 : 1][type]

                        MouseArea
                        {
                            anchors.fill: parent
                            drag.target: parent
                            property int startX: 0
                            property int startY: 0
                            onPressed:
                            {
                                console.log("On press: ", parent.x, parent.y);
                                startX = parent.x;
                                startY = parent.y;
                            }
                            onReleased:
                            {
                                var  fromX = startX / squareSize;
                                var fromY = startY / squareSize;
                                var toX   = (parent.x + mouseX) / squareSize;
                                var toY   = (parent.y + mouseY) / squareSize;
//                                if (!logic.move(fromX, fromY, toX, toY))
//                                {
//                                    parent.x = startX;
//                                    parent.y = startY;
//                                }
                                if(!game.makeMove(fromX,fromY,toX,toY))
                                {
                                    parent.x = startX;
                                    parent.y = startY;
                                }
                            }
                        }
                    }
                    Image
                    {
                        height: squareSize
                        width : squareSize

                        x: squareSize * positionX
                        y: squareSize * positionY
                        z: 1

                        source: images[2][(mark == true)? 0:1]

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
