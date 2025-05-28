//
// Created by Edy on 28/05/2025.
//

#include "Coin.h"

#include "AnimationV2.h"
#include "Resources.h"

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include "Physics.h"

Coin::~Coin() {
    if (body) { // Only destroy if not already destroyed
        Physics::world->DestroyBody(body);
        body = nullptr;
    }
}

void Coin::Begin() {

    tag= "coin";

    animation = AnimationV2(1.4f,
        {
    AnimFrame(1.3f, Resources::textures["coin14.png"]),
    AnimFrame(1.2f, Resources::textures["coin13.png"]),
    AnimFrame(1.1f, Resources::textures["coin12.png"]),
    AnimFrame(1.0f, Resources::textures["coin11.png"]),
    AnimFrame(0.9f, Resources::textures["coin10.png"]),
    AnimFrame(0.8f, Resources::textures["coin9.png"]),
    AnimFrame(0.7f, Resources::textures["coin8.png"]),
    AnimFrame(0.6f, Resources::textures["coin7.png"]),
    AnimFrame(0.5f, Resources::textures["coin6.png"]),
    AnimFrame(0.4f, Resources::textures["coin5.png"]),
    AnimFrame(0.3f, Resources::textures["coin4.png"]),
    AnimFrame(0.2f, Resources::textures["coin3.png"]),
    AnimFrame(0.1f, Resources::textures["coin2.png"]),
    AnimFrame(0.0f, Resources::textures["coin1.png"]),
    });

    b2BodyDef bodyDef{};
    bodyDef.position.Set(position.x, position.y);
    b2Body* body = Physics::world->CreateBody(&bodyDef);
    b2PolygonShape shape{};
    shape.SetAsBox(0.4f, 0.4f);

    FixtureData* fixtureData = new FixtureData();
    fixtureData->type=FixtureDataType::Object;
    fixtureData->object =this;


    b2FixtureDef fixtureDef{};
    fixtureDef.shape=&shape;
    fixtureDef.userData.pointer=(uintptr_t)fixtureData;
    fixtureDef.isSensor=true;
    fixtureDef.density = 0.0f;
    body ->CreateFixture(&fixtureDef);

}

void Coin::Update(float deltaTime) {

    animation.Update(deltaTime);
}

void Coin::Render(Renderer& renderer) {

    renderer.Draw(animation.GetTexture(),position, sf::Vector2f(0.8f,0.8f));
}