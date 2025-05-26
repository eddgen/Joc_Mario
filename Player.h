//
// Created by Edy on 25/05/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"
#include "Renderer.h"
#include "box2d/b2_body.h"
#include "Physics.h"


class Player
    :public ContactListener
{

public:
    void Begin();
    void Update(float deltaTime);
    void Draw(Renderer& renderer);

    virtual void OnBeginContact() override;
    virtual void OnEndContact() override;

    sf::Vector2f position{};
    float angle{};
private:
    Animation runAnimation;

    b2Body* body{};
    size_t isGrounded = 0;
    bool facingLeft = false;

};



#endif //PLAYER_H
