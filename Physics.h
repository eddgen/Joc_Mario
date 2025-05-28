//
// Created by Edy on 25/05/2025.
//

#ifndef PHYSICS_H
#define PHYSICS_H

#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>
#include "Renderer.h"

class Player; // Forward declaration
class Object; // Forward declaration
class MyDebugDraw;

class ContactListener {
public:
    virtual void OnBeginContact(b2Fixture* self, b2Fixture* other) = 0;
    virtual void OnEndContact(b2Fixture* self, b2Fixture* other) = 0;
    virtual ~ContactListener() = default;
};

enum class FixtureDataType {
    Player,
    MapTile,
    Object
};

struct FixtureData {
    FixtureDataType type;
    ContactListener* listener;
    union {
        Player* player;
        Object* object;
        struct { int mapX, mapY; };
    };
};

class Physics {
public:
    static void Init();
    static void Update(float deltaTime);
    static void DebugDraw(Renderer& renderer);

    static b2World* world;
    static MyDebugDraw* debugDraw;
};

#endif //PHYSICS_H

