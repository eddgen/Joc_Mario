//
// Created by Edy on 25/05/2025.
//

#ifndef PHYSICS_H
#define PHYSICS_H


#include <box2d/b2_world.h>
#include <box2d/b2_draw.h>
#include "Renderer.h"

class MyDebugDraw;

class ContactListener {
public:
    virtual void OnBeginContact()=0;
    virtual void OnEndContact() =0;
};

class Physics {
public:
    static void Init();
    static void Update(float deltaTime);
    static void DebugDraw(Renderer& renderer);


    static MyDebugDraw* debugDraw;
    static b2World world;
};



#endif //PHYSICS_H
