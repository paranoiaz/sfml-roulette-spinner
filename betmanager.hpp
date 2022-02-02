#ifndef BETMANAGER_HPP
#define BETMANAGER_HPP

#include <vector>
#include <algorithm>

class BetManager
{
private:
    // multipliers
    float multiplierRed;
    float multiplierGreen;
    float multiplierBlack;

    // bets
    float betAmountRed;
    float betAmountGreen;
    float betAmountBlack;

public:
    enum Tiles
    {
        Red,
        Black,
        Green
    };

    BetManager();
    ~BetManager();

    void insertBet(float betAmount, Tiles tileColor);
    float checkBets(int currentRoll);
    void clearBets();
};

#endif