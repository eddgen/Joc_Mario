#include "Player.h"
#include "Object.h"
#include "Resources.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include <iostream>
#include "Coin.h"
#include "Enemy.h"
#include "Game.h"

const float movementSpeed = 7.0f;
const float jumpVelocity = 15.0f;

Player::Player(sf::Texture* texture, float imageCountx, float switchTime) : animation(texture, imageCountx, switchTime) {
    if (!this->texture.loadFromFile("../resources/textures/Pink_Monster_Idle_4.png")) {
        std::cerr << "Failed to load Pink_Monster_Idle_4.png" << std::endl;
    }
}

void Player::Begin() {
    jumpSound.setBuffer(Resources::sounds["jump.wav"]);
    jumpSound.setVolume(15);

    fixtureData.type = FixtureDataType::Player;
    fixtureData.player = this;
    fixtureData.listener = this;

    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = true;
    body = Physics::world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef{};
    fixtureDef.userData.pointer = (uintptr_t)&fixtureData;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    b2CircleShape circleShape{};
    circleShape.m_radius = 0.375f;
    circleShape.m_p.Set(0.0f, -0.33f);
    fixtureDef.shape = &circleShape;
    body->CreateFixture(&fixtureDef);

    circleShape.m_p.Set(0.0f, 0.375f);
    body->CreateFixture(&fixtureDef);

    b2PolygonShape polygonShape{};
    polygonShape.SetAsBox(0.375f, 0.375f);
    fixtureDef.shape = &polygonShape;
    body->CreateFixture(&fixtureDef);

    polygonShape.SetAsBox(0.35, 0.2f, b2Vec2(0.0f, 0.55f), 0.0f);
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
    groundFixture = body->CreateFixture(&fixtureDef);
}

void Player::Update(float deltaTime) {
    if (isDead) return;

    float move = movementSpeed;
    bool isRunning = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

    if (isRunning) {
        move *= 2;
    }

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        facingLeft = false;
        velocity.x += move;
        if (isRunning && isGrounded && currentState != AnimationState::Running) {
            animation.Reconstruct(4, &texture, 6, 0.1f);
            currentState = AnimationState::Running;
        } else if (!isRunning && isGrounded && currentState != AnimationState::Walking) {
            animation.Reconstruct(3, &texture, 6, 0.2f);
            currentState = AnimationState::Walking;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        facingLeft = true;
        velocity.x -= move;
        if (isRunning && isGrounded && currentState != AnimationState::Running) {
            animation.Reconstruct(4, &texture, 6, 0.1f);
            currentState = AnimationState::Running;
        } else if (!isRunning && isGrounded && currentState != AnimationState::Walking) {
            animation.Reconstruct(3, &texture, 6, 0.2f);
            currentState = AnimationState::Walking;
        }
    } else if (isGrounded && velocity.x == 0.0f && currentState != AnimationState::Idle) {
        animation.Reconstruct(1, &texture, 4, 0.3f);
        currentState = AnimationState::Idle;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && isGrounded) {
        velocity.y = -jumpVelocity;
        jumpSound.play();
        if (currentState != AnimationState::Jumping) {
            animation.Reconstruct(2, &texture, 8, 0.1f);
            currentState = AnimationState::Jumping;
            jumpAnimationPlayed = false;
        }
    }

    animation.Update(deltaTime);

    if (!isGrounded && currentState != AnimationState::Jumping && currentState != AnimationState::Falling) {
        animation.Reconstruct(1, &texture, 4, 0.3f);
        currentState = AnimationState::Falling;
    }

    body->SetLinearVelocity(velocity);

    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * (180.0f / M_PI);
}

void Player::Draw(Renderer &renderer) {
    if (!isDead) {
        renderer.Drawp(animation.frameRect, texture, position, sf::Vector2f(facingLeft ? -1.5 : 1.5f, 1.5f), angle);
    }
}

void Player::OnBeginContact(b2Fixture* self, b2Fixture* other) {
    FixtureData* data = (FixtureData*)other->GetUserData().pointer;
    if (!data || !data->object) return;

    if (data->type == FixtureDataType::Object && data->object->tag == "coin") {
        Coin* coin = dynamic_cast<Coin*>(data->object);
        if (coin && !coin->isCollected) {
            coin->isCollected = true;
            std::cout << "coins = " << ++coins << "\n";
            objectsToDelete.push_back(data->object);
        }
    } else if (data->type == FixtureDataType::Object && data->object->tag == "enemy") {
        Enemy* enemy = dynamic_cast<Enemy*>(data->object);
        if (!enemy || enemy->IsDead()) return;

        // Get positions and velocity
        float playerY = body->GetPosition().y;
        float enemyY = enemy->body->GetPosition().y;
        float velocityY = body->GetLinearVelocity().y;

        // Check if player is above the enemy and moving downward
        if (playerY < enemyY && velocityY >= 0.0f) { // Player is above and falling
            std::cout << "Player landed on enemy" << std::endl;
            enemy->Die();
            objectsToDelete.push_back(enemy);
            // Apply a small bounce
            b2Vec2 velocity = body->GetLinearVelocity();
            velocity.y = -jumpVelocity * 0.5f;
            body->SetLinearVelocity(velocity);
        } else {
            // Player collides with enemy from side or below
            std::cout << "Player hit enemy (side or below)" << std::endl;
            isDead = true;
            paused = true;
        }
    } else {
        // Handle ground collision
        isGrounded++;
         if (isGrounded > 0 && currentState != AnimationState::Idle && currentState != AnimationState::Walking && currentState != AnimationState::Running) {
             animation.Reconstruct(1, &texture, 4, 0.3f);
             currentState = AnimationState::Idle;
             std::cout << "Landed (Idle)" << std::endl;
        }
    }
}

void Player::OnEndContact(b2Fixture* self, b2Fixture* other) {
    if (isGrounded > 0) {
        isGrounded--;
    }
}

size_t Player::GetCoins() {
    return coins;
}