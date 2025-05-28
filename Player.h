#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "box2d/b2_body.h"
#include "Animation.h"
#include "Renderer.h"
#include "Physics.h"

class Player : public ContactListener {
public:
    enum class AnimationState {
        Idle,
        Walking,
        Running,
        Jumping,
        Falling
    };

    Player(sf::Texture* texture, float imageCountx, float switchTime);
    void Begin();
    void Update(float deltaTime);
    void Draw(Renderer& renderer);

    void OnBeginContact(b2Fixture* self, b2Fixture* other) override;
    void OnEndContact(b2Fixture* self, b2Fixture* other) override;

    sf::Vector2f position{};
    float angle{};
    bool isDead{};

    size_t GetCoins();

private:
    FixtureData fixtureData{};
    Animation animation;
    sf::Texture texture;
    sf::Sound jumpSound;
    b2Body* body{};
    b2Fixture* groundFixture;

    size_t isGrounded = 0;
    bool facingLeft = false;
    AnimationState currentState = AnimationState::Idle;
    bool jumpAnimationPlayed = false;

    size_t coins{};
};

#endif //PLAYER_H