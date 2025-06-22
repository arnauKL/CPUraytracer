#pragma once

#include "Random.h"
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Renderer {

  public:
    Renderer();
    void render();
    void display(sf::RenderWindow &window);

  private:
    sf::Image _image;
    sf::Texture _texture;
    sf::Sprite _sprite;
    Random _rnd = Random(); // Random number generator

    sf::Color perPixel(sf::Vector2f);
};
