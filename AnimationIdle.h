//
// Created by Edy on 26/05/2025.
//

#ifndef ANIMATIONIDLE_H
#define ANIMATIONIDLE_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


class AnimationIdle {
public:
    AnimationIdle(sf::Texture* texture, float imageCountx, float switchTime);
    ~AnimationIdle();

    void Update(float deltaTime);

public:
    sf::IntRect frameRect;

    private:
    float imageCountx;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

};



#endif //ANIMATIONIDLE_H
