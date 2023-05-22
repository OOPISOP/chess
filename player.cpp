/***********************************************************************
 * File: Player.cpp
 * Author: B11115033
 * Create Date: 2023/05/10
 * Editor: B11115033
 * Update Date: 2023/05/10
 * Description: Player imp
***********************************************************************/
#include "Player.h"

Player::Player()
{
    this->whiteSide = true;
}
//Intent:set white side
//Pre:white side
//Pos:set white side
void Player::setWhiteSide(bool whiteSide)
{
    this->whiteSide = whiteSide;
}
//Intent:get white side
//Pre: white side
//Pos return white side
bool Player::getWhiteSide()
{
    return this->whiteSide;
}
//Intent:==operator
//Pre:player
//Pos:return bool
bool Player::operator==(const Player& rhs)
{
    if(this->whiteSide != rhs.whiteSide)return false;
    return true;
}
