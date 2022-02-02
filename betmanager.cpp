#include "betmanager.hpp"

BetManager::BetManager()
{
    // black and red 2x, green 14x
    this->multiplierRed = 2.0f;
    this->multiplierBlack = 2.0f;
    this->multiplierGreen = 14.0f;

    this->betAmountRed = 0.0f;
    this->betAmountBlack = 0.0f;
    this->betAmountGreen = 0.0f;
}

BetManager::~BetManager()
{
}

void BetManager::insertBet(float betAmount, Tiles tileColor)
{
    if (tileColor == Red)
    {
        this->betAmountRed += betAmount;
    }
    if (tileColor == Black)
    {
        this->betAmountBlack += betAmount;
    }
    if (tileColor == Green)
    {
        this->betAmountGreen += betAmount;
    }
}

float BetManager::checkBets(int currentRoll)
{
    float totalAmount = 0;
    std::vector<int> redTiles = {1, 3, 5, 7, 10, 12, 14};
    std::vector<int> blackTiles = {2, 4, 6, 9, 11, 13, 15};
    std::vector<int> greenTiles = {8};

    // check if roll in array
    if (std::find(redTiles.begin(), redTiles.end(), currentRoll) != redTiles.end())
    {
        totalAmount += this->betAmountRed * this->multiplierRed;
    }
    if (std::find(blackTiles.begin(), blackTiles.end(), currentRoll) != blackTiles.end())
    {
        totalAmount += this->betAmountBlack * this->multiplierBlack;
    }
    if (std::find(greenTiles.begin(), greenTiles.end(), currentRoll) != greenTiles.end())
    {
        totalAmount += this->betAmountGreen * this->multiplierGreen;
    }

    return totalAmount;
}

void BetManager::clearBets()
{
    // reset all the bet amounts
    this->betAmountRed = 0.0f;
    this->betAmountBlack = 0.0f;
    this->betAmountGreen = 0.0f;
}