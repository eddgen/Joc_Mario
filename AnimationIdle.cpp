//
// Created by Edy on 26/05/2025.
//

#include "AnimationIdle.h"
#include "SFML/Graphics.hpp"



AnimationIdle::AnimationIdle(sf::Texture* texture, float imageCountx, float switchTime)
{
    texture->loadFromFile("Pink_Monster_Idle_4.png");
    this->imageCountx = imageCountx;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    frameRect.width = texture->getSize().x / (float)imageCountx;
    frameRect.height = texture->getSize().y;
}

AnimationIdle::~AnimationIdle()
{
}

void AnimationIdle::Update(float deltaTime)
{

    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCountx)
        {
            currentImage.x = 0;
        }
    }

    frameRect.left = currentImage.x * frameRect.width; //offset pt unde ince rect al pozei cu mai multe frameuri
    frameRect.top =0;
}