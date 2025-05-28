#include "Physics.h"
#include <SFML/Graphics.hpp>
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_draw.h>

b2World* Physics::world = nullptr;
MyDebugDraw* Physics::debugDraw = nullptr;

class MyDebugDraw : public b2Draw {
public:
    MyDebugDraw(sf::RenderTarget& target) : target(target) {
        SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit);
    }

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        sf::ConvexShape shape(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(0.02f);
        shape.setOutlineColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                       (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 255)));
        target.draw(shape);
    }

    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        sf::ConvexShape shape(vertexCount);
        for (int i = 0; i < vertexCount; i++) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                     (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 120)));
        target.draw(shape);
    }

    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override {
        sf::CircleShape circle(radius);
        circle.setPosition(center.x, center.y);
        circle.setOrigin(radius, radius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(0.02f);
        circle.setOutlineColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                        (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 255)));
        target.draw(circle);
    }

    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override {
        sf::CircleShape circle(radius);
        circle.setPosition(center.x, center.y);
        circle.setOrigin(radius, radius);
        circle.setFillColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                      (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 180)));
        target.draw(circle);
        b2Vec2 p = center + (radius * axis);
        DrawSegment(center, p, color);
    }

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {
        sf::VertexArray va(sf::Lines, 2);
        sf::Color sfColor = sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                      (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 120));
        va[0].position = sf::Vector2f(p1.x, p1.y);
        va[0].color = sfColor;
        va[1].position = sf::Vector2f(p2.x, p2.y);
        va[1].color = sfColor;
        target.draw(va);
    }

    void DrawTransform(const b2Transform& xf) override {
        b2Vec2 p = xf.p;
        b2Vec2 px = p + (0.5f * xf.q.GetXAxis());
        b2Vec2 py = p + (0.5f * xf.q.GetYAxis());
        DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
        DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
    }

    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override {
        sf::CircleShape circle(size);
        circle.setPosition(p.x, p.y);
        circle.setOrigin(size, size);
        circle.setFillColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255),
                                      (sf::Uint8)(color.b * 255), (sf::Uint8)(color.a * 120)));
        target.draw(circle);
    }

private:
    sf::RenderTarget& target;
};

//static MyGlobalContactListener* contactListener = nullptr;

class MyGlobalContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override {
        FixtureData* dataA = (FixtureData*)contact->GetFixtureA()->GetUserData().pointer;
        FixtureData* dataB = (FixtureData*)contact->GetFixtureB()->GetUserData().pointer;

        if (dataA && dataA->listener) {
            dataA->listener->OnBeginContact(contact->GetFixtureA(), contact->GetFixtureB());
        }
        if (dataB && dataB->listener) {
            dataB->listener->OnBeginContact(contact->GetFixtureB(), contact->GetFixtureA());
        }
    }

    void EndContact(b2Contact* contact) override {
        FixtureData* dataA = (FixtureData*)contact->GetFixtureA()->GetUserData().pointer;
        FixtureData* dataB = (FixtureData*)contact->GetFixtureB()->GetUserData().pointer;

        if (dataA && dataA->listener) {
            dataA->listener->OnEndContact(contact->GetFixtureA(), contact->GetFixtureB());
        }
        if (dataB && dataB->listener) {
            dataB->listener->OnEndContact(contact->GetFixtureB(), contact->GetFixtureA());
        }
    }
};

void Physics::Init()
{
    if (world)
        delete world;

    world = new b2World(b2Vec2(0.0f, 35.2f));
    world->SetDebugDraw(debugDraw);
}

void Physics::Update(float deltaTime)
{
    world->Step(deltaTime, 8, 3);
    world->SetContactListener(new MyGlobalContactListener());
}

void Physics::DebugDraw(Renderer& renderer) {
    if (!debugDraw)
    {
        debugDraw = new MyDebugDraw(renderer.target);
        debugDraw->SetFlags(0u);//b2Draw::e_shapeBit
        world->SetDebugDraw(debugDraw);
    }

    world->DebugDraw();
}