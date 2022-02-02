#include "button.hpp"

Button::Button(std::string texturePath)
{
    this->texture = new sf::Texture();
    if (!this->texture->loadFromFile(texturePath))
    {
        std::cout << "error: failed to load image\n";
        std::exit(1);
    }
    this->sprite.setTexture(*this->texture);
}

Button::~Button()
{
    delete this->texture;
}

bool Button::isClicked(sf::Vector2f mousePosition) const
{
    return this->sprite.getGlobalBounds().contains(mousePosition);
}