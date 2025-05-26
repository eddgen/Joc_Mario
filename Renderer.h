//
// Created by Edy on 23/05/2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Renderer {

public:
    Renderer(sf::RenderTarget& target);

    void Draw( const sf::Texture& texture,
        const sf::Vector2f& position, const sf:: Vector2f& size,
        float angle =0.0f); //functie care ia textura folosind o variabila de tip texture in sfml
    // folosesec pt a desena orice textura pe ecrana a unui obiect

    void Drawp(sf::IntRect frame_rect,
               const sf::Texture &texture, const sf::Vector2f &position,
               const sf::Vector2f &size, float angle = 0.0f); //aceeasi functie da pt player
    sf::RenderTarget& target;

private:
    sf::Sprite sprite{};

};



#endif //RENDERER_H
