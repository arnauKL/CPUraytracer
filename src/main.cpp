#include "Renderer.h"
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

int main() {

    // Window settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(conf::W_WIDTH, conf::W_HEIGHT),
                            "CPU Raytracer", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Renderer renderer = Renderer();
    renderer.render();

    // Main loop
    while (window.isOpen()) {

        // Handle events
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R)
                    renderer.render();
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear();
        renderer.display(window);
        window.display();
    }
    return 0;
}
