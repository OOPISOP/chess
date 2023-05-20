#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    bool whiteSide;

    Player();

    void setWhiteSide(bool whiteSide);
    bool getWhiteSide();

    bool operator==(const Player& rhs);
};

#endif // PLAYER_H
