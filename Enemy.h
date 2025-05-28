//
// Created by Edy on 28/05/2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "AnimationV2.h"
#include "Object.h"
#include "Physics.h"

class Enemy
    :public Object
    {
        public:
        virtual void Begin() override;
        virtual void Update(float deltaTime) override;
        virtual void Render(Renderer& renderer) override;

        void Die();
        bool IsDead();

        bool isDead = false;

        b2Body* body{};

        private:
        AnimationV2 animation{};
        float movement = 5.0f;

        float destroyTimer = 0.0f;


        FixtureData fixtureData{};

};



#endif //ENEMY_H
