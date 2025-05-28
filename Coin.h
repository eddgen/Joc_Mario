//
// Created by Edy on 28/05/2025.
//

#ifndef COIN_H
#define COIN_H
#include "AnimationV2.h"
#include "Object.h"
#include "box2d/b2_body.h"


class Coin
    :public Object
{
    public:


    ~Coin();

    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer &renderer) override;
    b2Body *body{};
    bool isCollected = false;
private:
    AnimationV2 animation;


};



#endif //COIN_H
