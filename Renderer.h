#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Renderer {
public:
    Renderer(sf::RenderTarget& target);

    void Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, float angle = 0.0f);

    // Updated signature without numberofFrames
    void Drawp(sf::IntRect frame_rect, const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float angle = 0.0f);

    sf::RenderTarget& target;

private:
    sf::Sprite sprite{};
};

#endif //RENDERER_H