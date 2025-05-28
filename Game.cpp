#include "Game.h"
#include "Resources.h"
#include "Map.h"
#include "Physics.h"
#include "Player.h"
#include <filesystem>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Coin.h"
#include "Enemy.h"

Map map(1.0f);
Camera camera(20.0f);
sf::Music music;
Player* player = nullptr;
std::vector<Object*> objects;
std::vector<Object*> objectsToDelete; // Add this to track objects for deletion
bool paused{};
sf::Image mapImage{};
sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));
sf::Font font{};
sf::Text coinsText("Coins", font);
sf::Text gameOverText("Game Over! Press Space to Restart", font);

void Restart() {
    // Clear pending deletions
    objectsToDelete.clear();

    // Clear existing objects
    for (auto& object : objects) {
        if (object->tag == "enemy" || object->tag == "coin") {
            DeleteObject(object);
        }
    }
    objects.clear();

    // Reinitialize physics
    Physics::Init();

    // Recreate player
    delete player;
    sf::Texture* playerTexture = &Resources::textures["Pink_Monster_Idle_4.png"];
    player = new Player(playerTexture, 4, 0.3f);
    player->position = map.CreateFromImage(mapImage, objects);

    player->isDead = false;
    paused = false;

    player->Begin();
    for (auto& object : objects) {
        object->Begin();
    }

    music.play();
}

void Begin(const sf::Window& window) {
    for (auto& file : std::filesystem::directory_iterator("../resources/textures/")) {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }

    for (auto& file : std::filesystem::directory_iterator("../resources/sounds/")) {
        if (file.is_regular_file() && (file.path().extension() == ".wav" || file.path().extension() == ".ogg")) {
            Resources::sounds[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }

    if (!music.openFromFile("../resources/sounds/music.ogg")) {
        std::cerr << "Failed to load music.ogg" << std::endl;
        return;
    }
    music.setLoop(true);
    music.setVolume(50);

    font.loadFromFile("../resources/fonts/font.ttf");
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setOutlineColor(sf::Color::Blue);
    coinsText.setOutlineThickness(1.0f);
    coinsText.setScale(0.1f, 0.1f);

    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1.0f);
    gameOverText.setScale(0.1f, 0.1f);

    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setOrigin(sf::Vector2f(0.5f, 0.5f));

    Physics::Init();

    sf::Image image;
    image.loadFromFile("../resources/map.png");

    sf::Texture* playerTexture = &Resources::textures["Pink_Monster_Idle_4.png"];
    if (!playerTexture->loadFromFile("../resources/textures/Pink_Monster_Idle_4.png")) {
        std::cerr << "Failed to load Pink_Monster_Idle_4.png" << std::endl;
        return;
    }
    player = new Player(playerTexture, 4, 0.3f);
    player->position = map.CreateFromImage(image, objects);
    player->Begin();

    for (auto& object : objects) {
        object->Begin();
    }

    music.play();

    mapImage.loadFromFile("../resources/map.png");
}

void Update(float deltaTime) {
    if (player->isDead) {
        paused = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Restart();
        }
        return;
    }

    if (paused) return;

    Physics::Update(deltaTime);
    ProcessPendingDeletions(); // Process deletions after physics step

    player->Update(deltaTime);
    camera.position = player->position;

    for (auto& object : objects) {
        object->Update(deltaTime);
    }
}

void Render(Renderer& renderer) {
    renderer.Draw(Resources::textures["sky.png"], camera.position, camera.GetViewSize());
    map.Draw(renderer);
    if (player && !player->isDead) {
        player->Draw(renderer);
    }
    for (auto& object : objects) {
        object->Render(renderer);
    }
    Physics::DebugDraw(renderer);
}

void RenderUI(Renderer &renderer) {
    coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 1.0f));
    coinsText.setString("Coins: " + std::to_string(player->GetCoins()));
    renderer.target.draw(coinsText);

    if (paused || player->isDead) {
        backgroundShape.setScale(camera.GetViewSize());
        renderer.target.draw(backgroundShape);
        gameOverText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 2.0f));
        renderer.target.draw(gameOverText);
    }
}

void DeleteObject(Object *object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        if (object->tag == "coin") {
            Coin* coin = dynamic_cast<Coin*>(*it);
            if (coin && coin->body) {
                Physics::world->DestroyBody(coin->body);
                coin->body = nullptr;
            }
        } else if (object->tag == "enemy") {
            Enemy* enemy = dynamic_cast<Enemy*>(*it);
            if (enemy && enemy->body) {
                Physics::world->DestroyBody(enemy->body);
                enemy->body = nullptr;
            }
        }
        delete *it;
        objects.erase(it);
    }
}

void ProcessPendingDeletions() {
    for (auto* object : objectsToDelete) {
        DeleteObject(object);
    }
    objectsToDelete.clear();
}