#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "spinner.hpp"
#include "player.hpp"
#include "betmanager.hpp"
#include "button.hpp"

class WindowManager
{
private:
    // window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    // objects
    Spinner *spinner;
    Player *player;
    BetManager *betManager;

    // text
    sf::Text countdownTimerText;
    sf::Text amountCoinsText;

    // buttons
    Button *buttonRed;
    Button *buttonGreen;
    Button *buttonBlack;

    void initWindow();
    void initObjects();
    void initText();
    void initButtons();
    void pollEvents();
    void checkClock();
    std::string formatFloat(float value);

public:
    WindowManager();
    ~WindowManager();

    void update();
    void render();
    bool isOpen() const;
};

#endif