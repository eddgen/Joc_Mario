#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderTarget &target) : target(target) {
}

void Renderer::Draw(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float angle) {
    sprite.setTexture(texture, true);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
    sprite.setRotation(angle);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size.x / texture.getSize().x, size.y / texture.getSize().y));
    target.draw(sprite);
}

void Renderer::Drawp(sf::IntRect frame_rect, const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float angle) {
    sprite.setTexture(texture, true);
    sprite.setTextureRect(frame_rect);
    sprite.setOrigin(sf::Vector2f(frame_rect.width / 2.0f, frame_rect.height / 2.0f));
    sprite.setRotation(angle);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size.x / frame_rect.width, size.y / frame_rect.height));
    target.draw(sprite);
}