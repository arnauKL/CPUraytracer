#include "Renderer.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

Renderer::Renderer() {

    _image = sf::Image();
    _image.create(conf::W_WIDTH, conf::W_HEIGHT, sf::Color::Blue);

    _texture = sf::Texture();
    _texture.loadFromImage(_image);

    _sprite = sf::Sprite(_texture);
}

void Renderer::render() {
    for (int y = 0; y < conf::W_HEIGHT; y++) {
        for (int x = 0; x < conf::W_WIDTH; x++) {
            auto coord = sf::Vector2f((float)x / (float)conf::W_WIDTH, (float)y / (float)conf::W_HEIGHT);
            coord.x = coord.x * 2.0f - 1.0f; // Normalise btween -1 and 1, easier this way bcs
                                             // 0,0 *is* the center of the image and the view
            coord.y = coord.y * 2.0f - 1.0f;
            _image.setPixel(x, y, perPixel(coord));
        }
    }

    _texture.update(_image);
    _sprite = sf::Sprite(_texture);
}

void Renderer::display(sf::RenderWindow &window) { window.draw(_sprite); }

sf::Color Renderer::perPixel(sf::Vector2f coord) {

    sf::Vector3f rayOrigin = sf::Vector3f(0.0f, 0.0f, 2.0f); // This is the location of the camera
                                                             // with respect to the screen plane
    sf::Vector3f rayDirection = sf::Vector3f(coord.x, coord.y, -1.0f);
    float radius = 0.5f; // Radius of the sphere (only one for now)

    // quadratic components to check for sphere collisions
    // formula:
    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
    // on:
    // a = origen del ray
    // b = direcció
    // r = sphere radius
    // t = hit distance (along the ray)
    float a = rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z; // essentially, dot product
    float b = 2.0f * (rayOrigin.x * rayDirection.x + rayOrigin.y * rayDirection.z + rayOrigin.z * rayDirection.z);
    float c = (rayOrigin.x * rayOrigin.x + rayOrigin.y * rayOrigin.y + rayOrigin.z * rayOrigin.z) - radius * radius;

    // There will only be hit when the discriminant is >= 0 (the sqrt(b^2 - 4ac))
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant >= 0) {
        return sf::Color::White;
    }

    return sf::Color::Black;
}
