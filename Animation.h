#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Animation {
public:
    Animation(sf::Texture* texture, float imageCountx, float switchTime);
    ~Animation();
    void Reconstruct(int whichTexture, sf::Texture* texture, float imageCountx, float switchTime);
    void Update(float deltaTime);
    bool IsCycleComplete() const; // Add this method

public:
    sf::IntRect frameRect;
    float switchTime;
    float imageCountx;

private:
    sf::Vector2u currentImage;
    float totalTime;
};

#endif //ANIMATION_H