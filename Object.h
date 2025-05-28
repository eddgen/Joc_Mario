//
// Created by Edy on 28/05/2025.
//

#ifndef OBJECT_H
#define OBJECT_H


#include "Renderer.h"

class Object
{
public:
    virtual void Begin() {}
    virtual void Update(float deltaTime) {}
    virtual void Render(Renderer& renderer) {}

    std::string tag{};

    sf::Vector2f position{};
    float angle{};
};

#endif //OBJECT_H
