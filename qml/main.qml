/***********************************************************************
 * File: main.qml
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: this is main view manager
***********************************************************************/
import QtQuick 2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.3
import QtMultimedia

ApplicationWindow
{
    id: root
    title: qsTr("Chess")
    visible: true
    minimumWidth: 8 * squareSize + 200
    minimumHeight: 8 * squareSize + menuBarHeight + 20

    property int squareSize: 80
    property int menuBarHeight:30
    property  int fenInputHeight: 20

    menuBar:MenuBar
    {
        height: menuBarHeight
           Menu
           {
               title: "Game"
               Action
               {
                   text: "Noraml(White First)"
                   onTriggered : game.newGame(true)
               }
               Action
               {
                   text: "Black First"
                   onTriggered : game.newGame(false)
               }

           }

           Menu
           {
               title: "Edit"
               Action
               {
                   text: "Undo"
                   shortcut: "Ctrl+u"
                   onTriggered : game.undo()
               }
               Action
               {
                   text: "Redo"
                   shortcut: "Ctrl+r"
                   onTriggered : game.redo()
               }
           }
       }
    property var images:
        [
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
    property int countdownTimeOne: 600 // 設定倒計時時間（以秒為單位）
    property int remainingTimeOne: countdownTimeOne // 剩餘時間

    property int countdownTimeTwo: 600 // 設定倒計時時間（以秒為單位）
    property int remainingTimeTwo: countdownTimeTwo // 剩餘時間

    Timer
    {
        id: countdownTimerOne
        interval: 1000 // 每秒更新一次
        running: false // 初始狀態停止計時器
        repeat: true
        onTriggered:
        {
            remainingTimeOne -= 1 // 每次觸發減少1秒
            if (remainingTimeOne <= 0)
            {
                countdownTimerOne.stop() // 時間到停止計時器
                game.timeUp(false)
            }
        }
    }

    Timer
    {
        id: countdownTimerTwo
        interval: 1000 // 每秒更新一次
        running: false // 初始狀態停止計時器
        repeat: true
        onTriggered:
        {
            remainingTimeTwo -= 1 // 每次觸發減少1秒
            if (remainingTimeTwo <= 0)
            {
                countdownTimerTwo.stop() // 時間到停止計時器
                game.timeUp(true)
            }
        }
    }


    Text
    {
      x: 8 * squareSize + 100
      text: Math.floor(Math.abs(remainingTimeOne/60)).toString() + ":" + (remainingTimeOne%60).toString() // 顯示剩餘時間
      font.pixelSize: 32
    }

    Text
    {
      x: 8 * squareSize + 100
      y: 500
      text: Math.floor(Math.abs(remainingTimeTwo/60)).toString() + ":" + (remainingTimeTwo%60).toString() // 顯示剩餘時間
      font.pixelSize: 32
    }
    TextField
    {
        height: fenInputHeight
        width: 8 * squareSize
        anchors.top: parent.top
        placeholderText: "Enter FEN here"
        onAccepted:
        {
            if(game.setFEN(text))
            {
                console.log("User input: " + text)
            }
        }
    }

    Component
    {
        // First screen
        id: gameBoard
        Item {
            Image
            {
                id: board
                y:fenInputHeight
                source: "/images/chess_board.jpg"
                height: 8 * squareSize
                width: 8 * squareSize
            }
        }
    }
    Component
    {
        id: chessPlacement
        Item
        {
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
                        y: fenInputHeight + squareSize * positionY
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
                                var fromY = (startY - fenInputHeight) / squareSize;
                                game.showNextMove(fromX,fromY)
                            }
                            onReleased:
                            {
                                var fromX = startX / squareSize;
                                var fromY = (startY - fenInputHeight) / squareSize;
                                var toX   = (parent.x + mouseX) / squareSize;
                                var toY   = (parent.y + mouseY - fenInputHeight) / squareSize;
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
                        y: fenInputHeight + squareSize * positionY
                        source: images[2][(mark == true)? 0:1]
                    }

                }
            }
        }


    }

    property int promotionX
    property int promotionY
    property  bool promotionWhite

    Connections
    {
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
            function onClockStart(white)
            {
                if(!white)
                {
                    countdownTimerOne.start()
                    countdownTimerTwo.stop()
                }
                else
                {
                    countdownTimerTwo.start()
                    countdownTimerOne.stop()
                }
            }
            function onResetClockTime()
            {
                countdownTimerOne.stop()
                countdownTimerTwo.stop()
                remainingTimeOne = 600
                remainingTimeTwo = 600
            }
        }

    property var promotionImage:
        [
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
        height: 4*squareSize + fenInputHeight
        width : squareSize
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape

        Column
        {
               anchors.centerIn: parent
               Repeater
               {
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
                                myPopup.close()
                                game.promotion(promotionX,promotionY,index);
                           }
                       }
                   }
               }
        }
    }
    Component {
        id: mainScreen
        Item
        {

            Loader {sourceComponent: gameBoard}
            Loader {sourceComponent: chessPlacement}
        }
    }
    StackView
    {
        id: screen
        anchors.fill: parent
        initialItem: mainScreen
    }
}
