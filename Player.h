/***********************************************************************
 * File: Player.h
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Player class define
***********************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    bool whiteSide;

    Player();

    void setWhiteSide(bool whiteSide);//set white side
    bool getWhiteSide();//get white side

    bool operator==(const Player& rhs);//
};

#endif // PLAYER_H
