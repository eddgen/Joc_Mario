//
// Created by Edy on 23/05/2025.
//

#include "Renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderTarget &target)
    :target(target)
{
}

void Renderer::Draw( const sf::Texture &texture,
                     const sf::Vector2f &position,const sf::Vector2f &size, float angle) {

    sprite.setTexture(texture, true);
    sprite.setOrigin (sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2)); //originea pozei nu in colt dreapta sus ci in mijloc
    sprite.setRotation(angle);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size.x/texture.getSize().x,
        size.y/texture.getSize().y)); //sa isi dea render la o anumita scala indiferent de sizeul texturii

    target.draw(sprite);
}

void Renderer::Drawp(sf::IntRect frame_rect,const sf::Texture &texture,
                     const sf::Vector2f &position,const sf::Vector2f &size, float angle) {

    sprite.setTexture(texture, true);
    sprite.setTextureRect(frame_rect);
    sprite.setOrigin (sf::Vector2f(texture.getSize().x/2/4,texture.getSize().y/2)); //originea pozei nu in colt dreapta sus ci in mijloc ,
    //4 este cate frameuri are pngu hardcodat, trebuie schimabat manual si aici si la scale
    sprite.setRotation(angle);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size.x/(texture.getSize().x/4),
        size.y/texture.getSize().y)); //sa isi dea render la o anumita scala indiferent de sizeul texturii

    target.draw(sprite);
}
