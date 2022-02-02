#include "windowmanager.hpp"

void WindowManager::initWindow()
{
    std::string windowTitle = "Roulette Spinner";
    unsigned int windowWidth = 1200;
    unsigned int windowHeight = 800;

    this->videoMode.width = windowWidth;
    this->videoMode.height = windowHeight;
    this->window = new sf::RenderWindow(this->videoMode, windowTitle, sf::Style::Titlebar | sf::Style::Close);
}

void WindowManager::initObjects()
{
    this->spinner = new Spinner();
    this->player = new Player();
    this->betManager = new BetManager();
}

void WindowManager::initText()
{
    sf::Font *font = new sf::Font();
    if (!font->loadFromFile("./assets/arial.ttf"))
    {
        std::cout << "error: failed to load font\n";
        std::exit(1);
    }

    // text styling and positioning
    this->amountCoinsText.setString("100.00");
    this->amountCoinsText.setCharacterSize(20);
    this->amountCoinsText.setLetterSpacing(1);
    this->amountCoinsText.setStyle(sf::Text::Bold);
    this->amountCoinsText.setFillColor(sf::Color::White);
    this->amountCoinsText.setFont(*font);
    this->amountCoinsText.setPosition(sf::Vector2f(120.0f, 110.0f));

    this->countdownTimerText.setString("ROLLING IN 15.00");
    this->countdownTimerText.setCharacterSize(30);
    this->countdownTimerText.setLetterSpacing(2);
    this->countdownTimerText.setStyle(sf::Text::Bold);
    this->countdownTimerText.setFillColor(sf::Color::White);
    this->countdownTimerText.setFont(*font);

    // center text on window
    sf::FloatRect countdownBounds = this->countdownTimerText.getGlobalBounds();
    this->countdownTimerText.setOrigin(countdownBounds.left + countdownBounds.width / 2.0f, countdownBounds.top + countdownBounds.height / 2.0f);
    this->countdownTimerText.setPosition(sf::Vector2f(this->window->getSize().x / 2.0f, this->window->getSize().y / 2.0f));
}

void WindowManager::initButtons()
{
    float positionX = 140.0f;
    float positionY = 500.0f;
    float spacingX = 340.0f;

    this->buttonRed = new Button("./assets/red-bet-button.png");
    this->buttonGreen = new Button("./assets/green-bet-button.png");
    this->buttonBlack = new Button("./assets/black-bet-button.png");

    this->buttonRed->sprite.move(positionX, positionY);
    this->buttonGreen->sprite.move(positionX += spacingX, positionY);
    this->buttonBlack->sprite.move(positionX += spacingX, positionY);
}

void WindowManager::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            // check if spinner is not moving and balance is not negative
            if (this->spinner->scrollDistance > 0 || this->player->amountCoins <= 0.0f)
            {
                return;
            }

            // check if clicked on a button
            float betAmount = 1.0f;
            sf::Vector2f mousePosition(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
            if (this->buttonRed->isClicked(mousePosition))
            {
                this->betManager->insertBet(betAmount, BetManager::Red);
                this->player->amountCoins -= betAmount;
            }
            else if (this->buttonBlack->isClicked(mousePosition))
            {
                this->betManager->insertBet(betAmount, BetManager::Black);
                this->player->amountCoins -= betAmount;
            }
            else if (this->buttonGreen->isClicked(mousePosition))
            {
                this->betManager->insertBet(betAmount, BetManager::Green);
                this->player->amountCoins -= betAmount;
            }

            break;
        }
    }
}

void WindowManager::checkClock()
{
    // check if 15 seconds passed and spin
    this->spinner->timeLeft = this->spinner->spinTimer.asSeconds() - this->spinner->clock.getElapsedTime().asSeconds();
    if (this->spinner->clock.getElapsedTime() > this->spinner->spinTimer)
    {
        if (this->spinner->scrollDistance <= 0)
        {
            this->spinner->spin(5);
        }
    }
    else
    {
        this->countdownTimerText.setString("ROLLING IN " + this->formatFloat(this->spinner->timeLeft));
    }
}

std::string WindowManager::formatFloat(float value)
{
    // format float to use 2 decimal points
    std::string floatString = std::to_string(value);
    return floatString.substr(0, floatString.find(".") + 3);
}

WindowManager::WindowManager()
{
    this->initWindow();
    this->initObjects();
    this->initText();
    this->initButtons();
}

WindowManager::~WindowManager()
{
    // deallocate window
    delete this->window;

    // deallocate objects
    delete this->spinner;
    delete this->player;
    delete this->betManager;

    // deallocate buttons
    delete this->buttonRed;
    delete this->buttonGreen;
    delete this->buttonBlack;
}

void WindowManager::update()
{
    this->pollEvents();
    this->checkClock();

    this->amountCoinsText.setString(this->formatFloat(this->player->amountCoins));

    // decreasing speed for spinner
    if (this->spinner->scrollDistance > 0)
    {
        // if close to target set speed to constant
        if (this->spinner->scrollDistance > 150)
        {
            float directionX = this->spinner->scrollDistance / -1000.0f;
            this->spinner->move(directionX, 0.0f);
            this->spinner->scrollDistance += directionX;
        }
        else
        {
            float directionX = -0.2f;
            this->spinner->move(directionX, 0.0f);
            this->spinner->scrollDistance += directionX;
        }
    }

    // restart clock and process bets when timer is done
    if (this->spinner->scrollDistance < 0 && this->spinner->timeLeft < 0)
    {
        this->player->amountCoins += this->betManager->checkBets(this->spinner->currentRoll);
        this->betManager->clearBets();
        this->spinner->clock.restart();
    }
}

void WindowManager::render()
{
    this->window->clear();

    // render frames and tiles
    this->window->draw(this->spinner->backgroundFrame);
    for (sf::Sprite sprite : this->spinner->sprites)
    {
        this->window->draw(sprite);
    }
    this->window->draw(this->spinner->foregroundFrame);

    // render timer and amount
    this->window->draw(this->countdownTimerText);
    this->window->draw(this->amountCoinsText);

    // render buttons
    this->window->draw(this->buttonRed->sprite);
    this->window->draw(this->buttonGreen->sprite);
    this->window->draw(this->buttonBlack->sprite);

    this->window->display();
}

bool WindowManager::isOpen() const
{
    return this->window->isOpen();
}