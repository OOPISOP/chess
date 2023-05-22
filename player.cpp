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

