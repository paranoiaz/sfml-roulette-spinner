#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:
    sf::Texture *texture;

public:
    sf::Sprite sprite;

    Button(std::string texturePath);
    ~Button();

    bool isClicked(sf::Vector2f mousePosition) const;
};

#endif