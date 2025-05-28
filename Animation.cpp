#include "Animation.h"
#include "SFML/Graphics.hpp"

Animation::Animation(sf::Texture* texture, float imageCountx, float switchTime) {
    this->imageCountx = imageCountx;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    frameRect.width = texture->getSize().x / static_cast<int>(imageCountx);
    frameRect.height = texture->getSize().y;
}

Animation::~Animation() {
}

void Animation::Reconstruct(int whichTexture, sf::Texture* texture, float imageCountx, float switchTime) {
    if (whichTexture == 1) {
        texture->loadFromFile("../resources/textures/Pink_Monster_Idle_4.png");
    } else if (whichTexture == 2) {
        texture->loadFromFile("../resources/textures/Pink_Monster_Jump_8.png");
    } else if (whichTexture == 3) {
        texture->loadFromFile("../resources/textures/Pink_Monster_Walk_6.png");
    } else if (whichTexture == 4) {
        texture->loadFromFile("../resources/textures/Pink_Monster_Run_6.png");
    }
    this->imageCountx = imageCountx;
    this->switchTime = switchTime;
    // Preserve current frame to avoid resetting to first frame
    if (currentImage.x >= static_cast<int>(imageCountx)) {
        currentImage.x = 0;
    }

    frameRect.width = texture->getSize().x / static_cast<int>(imageCountx);
    frameRect.height = texture->getSize().y;
    frameRect.left = currentImage.x * frameRect.width;
    frameRect.top = 0;
}

void Animation::Update(float deltaTime) {
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= static_cast<int>(imageCountx)) {
            currentImage.x = 0;
        }
        frameRect.left = currentImage.x * frameRect.width;
        frameRect.top = 0;
    }
}

bool Animation::IsCycleComplete() const {
    return currentImage.x == 0 && totalTime < switchTime;
}