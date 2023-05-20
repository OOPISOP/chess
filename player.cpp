#include "Player.h"

Player::Player()
{
    this->whiteSide = true;
<<<<<<< HEAD

}


bool Player::isWhiteSide()
{
    return this->whiteSide;
}

void Player::setSide(bool whiteSide)
=======
}

void Player::setWhiteSide(bool whiteSide)
>>>>>>> 512f4a0 (f)
{
    this->whiteSide = whiteSide;
}

<<<<<<< HEAD
=======
bool Player::getWhiteSide()
{
    return this->whiteSide;
}

>>>>>>> 512f4a0 (f)
bool Player::operator==(const Player& rhs)
{
    if(this->whiteSide != rhs.whiteSide)return false;
    return true;
}
