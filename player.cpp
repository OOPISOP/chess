#include "Player.h"

Player::Player()
{
    this->whiteSide = true;
}

void Player::setWhiteSide(bool whiteSide)
{
    this->whiteSide = whiteSide;
}

bool Player::getWhiteSide()
{
    return this->whiteSide;
}

bool Player::operator==(const Player& rhs)
{
    if(this->whiteSide != rhs.whiteSide)return false;
    return true;
}
