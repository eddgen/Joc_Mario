//
// Created by Edy on 25/05/2025.
//

#include "Player.h"

#include "AnimationIdle.h"
#include "Game.h"
#include "AnimationIdle.h"
#include "Resources.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"

const float movementSpeed = 7.0f;
const float jumpVelocity = 10.0f;
sf::Texture idleTexture;


AnimationIdle animationIdle(&idleTexture, 4, 0.3f);

void Player::Begin() {


    //idleTexture.loadFromFile("../Pink_Monster_Idle_4.png");

    // runAnimation = Animation(0.4f,
    //     {
    //             AnimFrame(0.2f, Resources::textures["gray_brick.png"]),
    //             AnimFrame(0.0f, Resources::textures["Pink_Monster.png"])
    //     });

    //am facut playeru l o capsula
    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = true;
    body = Physics::world.CreateBody(&bodyDef);


    b2FixtureDef fixtureDef{};

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f; //setam manual velocitatea, nu avem nevoie de frictiunue pt ca am putea ramane lipiti de perete

    b2CircleShape circleShape{};
    circleShape.m_radius = 0.375f;
    circleShape.m_p.Set(0.0f, -0.33f);
    fixtureDef.shape = &circleShape;
    body->CreateFixture(&fixtureDef);

    // Top circle
    circleShape.m_p.Set(0.0f, 0.375f);
      // Set userData
    body->CreateFixture(&fixtureDef);

    b2PolygonShape polygonShape{};
    polygonShape.SetAsBox(0.375f, 0.375f); //half of player's size
    fixtureDef.shape = &polygonShape;
    body->CreateFixture(&fixtureDef);

    polygonShape.SetAsBox(0.35,0.2f, b2Vec2(0.0f,0.55f), 0.0f); //senzor pt detectarea coliziunilor, e doar senzor pt a sti cand caracterul e pe pamant
    fixtureDef.userData.pointer = (uintptr_t)this;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
}

void Player::Update(float deltaTime) {
    //idleTexture.loadFromFile("../Pink_Monster_Idle_4.png");
    float move=movementSpeed;

    animationIdle.Update(deltaTime);
    //runAnimation.Update(deltaTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        move*=2;

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x=0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        facingLeft=false;
        velocity.x +=move;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -=move;
        facingLeft=true;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isGrounded)
        velocity.y = -jumpVelocity;


    body->SetLinearVelocity(velocity);

    position=sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() *(180.0f/M_PI); //convertire din radiani in grade


}

void Player::Draw(Renderer &renderer) {
    //idleTexture.loadFromFile("../Pink_Monster_Idle_4.png");

    renderer.Drawp(animationIdle.frameRect,idleTexture,
                   position, sf::Vector2f(facingLeft ? -1.5 :1.5f,1.5f), angle);

}

void Player::OnBeginContact()
{
    isGrounded++;
}

void Player::OnEndContact()
{
    if (isGrounded>0)
        isGrounded--;
}