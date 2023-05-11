#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    bool whiteSide;
    Player();
    void setSide(bool whiteSide);
    bool isWhiteSide();
    bool operator==(const Player& rhs);
};

#endif // PLAYER_H
