#include "spinner.hpp"

void Spinner::initTextures()
{
    // using layers to stack frames
    sf::Texture *textureBackground = new sf::Texture();
    sf::Texture *textureForeground = new sf::Texture();
    if (!textureBackground->loadFromFile("./assets/background-frame.png"))
    {
        std::cout << "error: failed to load image\n";
        std::exit(1);
    }
    if (!textureForeground->loadFromFile("./assets/foreground-frame.png"))
    {
        std::cout << "error: failed to load image\n";
        std::exit(1);
    }

    this->backgroundFrame.setTexture(*textureBackground);
    this->foregroundFrame.setTexture(*textureForeground);

    // load all textures
    this->amountOfTextures = 15;
    for (unsigned int i = 1; i <= this->amountOfTextures; i++)
    {
        sf::Texture texture;
        std::vector<int> redTiles = {1, 3, 5, 7, 10, 12, 14};
        std::vector<int> blackTiles = {2, 4, 6, 9, 11, 13, 15};
        std::vector<int> greenTiles = {8};
        if (std::find(redTiles.begin(), redTiles.end(), i) != redTiles.end())
        {
            if (!texture.loadFromFile("./assets/red-tile.png"))
            {
                std::cout << "error: failed to load image\n";
                std::exit(1);
            }
        }
        else if (std::find(blackTiles.begin(), blackTiles.end(), i) != blackTiles.end())
        {
            if (!texture.loadFromFile("./assets/black-tile.png"))
            {
                std::cout << "error: failed to load image\n";
                std::exit(1);
            }
        }
        else if (std::find(greenTiles.begin(), greenTiles.end(), i) != greenTiles.end())
        {
            if (!texture.loadFromFile("./assets/green-tile.png"))
            {
                std::cout << "error: failed to load image\n";
                std::exit(1);
            }
        }

        texture.setSmooth(true);
        this->textures.push_back(texture);
    }
}

void Spinner::initSprites(int loopAmount)
{
    // load textures on sprites
    this->amountOfSprites = 15;
    float positionX = 0.0f;
    float positionY = 200.0f;
    while (loopAmount--)
    {
        for (unsigned int i = 0; i < this->amountOfSprites; i++)
        {
            sf::Sprite sprite;
            sprite.setTexture(this->textures[i]);
            sprite.move(positionX, positionY);
            positionX += sprite.getTexture()->getSize().x * this->spriteScale;
            sprite.scale(this->spriteScale, this->spriteScale);
            this->sprites.push_back(sprite);
        }
    }
}

Spinner::Spinner()
{
    this->spriteScale = 0.2f;
    this->spinTimer = sf::seconds(15.0f);

    this->initTextures();
    this->initSprites(1);
}

Spinner::~Spinner()
{
}

void Spinner::move(float directionX, float directionY)
{
    for (sf::Sprite &sprite : this->sprites)
    {
        sprite.move(directionX, directionY);
    }
}

void Spinner::spin(int amountOfSpins)
{
    // remove unused sprites from memory
    if (this->sprites.size() > 200)
    {
        this->sprites.erase(this->sprites.begin(), this->sprites.begin() + 200);
    }

    int randomNumber = 1 + std::rand() % 15;
    this->currentRoll = randomNumber;

    // we add 3 to the amount of spins to prevent seeing the end of the spinner
    this->initSprites(amountOfSpins + 3);

    int amountOfLoops = (this->sprites[0].getTexture()->getSize().x * this->spriteScale) * this->amountOfSprites;
    // add 1 to the amount of spins to spin longer
    this->scrollDistance = (amountOfSpins + 1) * amountOfLoops + (randomNumber * (this->sprites[0].getTexture()->getSize().x * this->spriteScale)) - 650;
}