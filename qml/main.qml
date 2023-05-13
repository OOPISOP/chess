import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

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
                        id: chessImage
                        height: squareSize
                        width : squareSize

                        x: squareSize * positionX
                        y: squareSize * positionY
                        source: images[(side == true) ? 0 : 1][type]

                        MouseArea
                        {
                            anchors.fill: parent
                            drag.target: parent
                            property int startX: 0
                            property int startY: 0
                            onPressed :
                            {
                                chessImage.z += 100;
                                startX = parent.x;
                                startY = parent.y;
                                var  fromX = startX / squareSize;
                                var fromY = startY / squareSize;
                                game.showNextMove(fromX,fromY)
                            }
                            onReleased:
                            {
                                var fromX = startX / squareSize;
                                var fromY = startY / squareSize;
                                var toX   = (parent.x + mouseX) / squareSize;
                                var toY   = (parent.y + mouseY) / squareSize;
                                console.log("On press: ", toX, toY);
                                if(toX>8||toX<0||toY>8||toY<0||!game.makeMove(fromX,fromY,toX,toY))
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
                        source: images[2][(mark == true)? 0:1]
                    }

                }
            }
        }


    }

    property int promotionX
    property int promotionY
    property  bool promotionWhite

    Connections {
            target: game
            function onShowPopup(x,y,w)
            {
                        myPopup.open()
                        myPopup.x = squareSize*x
                        myPopup.y = squareSize*y
                        if(!w)
                        {
                            myPopup.y -= 4*squareSize
                        }
                        promotionX = x
                        promotionY = y
                        promotionWhite = w

            }
        }

    property var promotionImage: [
        [
            "/images/white_rook.svg",
            "/images/white_bishop.svg",
            "/images/white_knight.svg",
            "/images/white_queen.svg",
        ],

        [
            "/images/black_rook.svg",
            "/images/black_bishop.svg",
            "/images/black_knight.svg",
            "/images/black_queen.svg",
        ],

    ]


    Popup
    {
        id: myPopup
        objectName: "myPopup"
        height: 4*squareSize
        width : squareSize
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape

        Column
        {
               anchors.centerIn: parent
               Repeater {
                   model: 4
                   Image
                   {
                       source: promotionImage[promotionWhite==true?0:1][index]
                       width: squareSize
                       height: squareSize
                       MouseArea
                       {
                           anchors.fill: parent
                           onClicked:
                           {
                                game.promotion(promotionX,promotionY,index);
                                myPopup.close()
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
        }
    }
    StackView {
        id: screen
        anchors.fill: parent
        initialItem: mainScreen
    }
}
