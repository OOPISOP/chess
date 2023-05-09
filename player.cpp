#include "Player.h"

Player::Player()
{
    this->whiteSide = true;

}


bool Player::isWhiteSide()
{
    return this->whiteSide;
}

void Player::setSide(bool whiteSide)
{
    this->whiteSide = whiteSide;
}

bool Player::operator==(const Player& rhs)
{
    if(this->whiteSide != rhs.whiteSide)return false;
    return true;
}
