#ifndef SPINNER_HPP
#define SPINNER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Spinner
{
private:
    std::vector<sf::Texture> textures;
    int amountOfTextures;
    int amountOfSprites;

    void initTextures();
    void initSprites(int loopAmount);

public:
    std::vector<sf::Sprite> sprites;
    sf::Sprite foregroundFrame;
    sf::Sprite backgroundFrame;

    // tiles movement and scaling
    float spriteScale;
    float scrollDistance;

    // spinner variables
    sf::Clock clock;
    sf::Time spinTimer;
    float timeLeft;
    float currentRoll;

    Spinner();
    ~Spinner();

    void move(float directionX, float directionY);
    void spin(int amountOfSpins);
};

#endif