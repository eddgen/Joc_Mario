//
// Created by Edy on 23/05/2025.
//

#include "Game.h"

#include <SFML/Graphics/CircleShape.hpp>
#include "Resources.h"
#include <filesystem>
#include <iostream>
#include "Map.h"
#include "Physics.h"
#include "Player.h"

Map map(1.0f);
Camera camera(20.0f);

Player player;



void Begin(const sf::Window& window) {


    for (auto& file : std::filesystem::directory_iterator("../resources/"))
    {

        if (file.is_regular_file() && file.path().extension() == ".png") {
            Resources::textures[file.path().filename().string()].loadFromFile(
                file.path().string());
        }
    }
    Physics::Init();

    sf::Image image;
    image.loadFromFile("../resources/map.png");
    player.position = map.CreateFromImage(image);
    player.Begin();


}

void Update(float deltaTime) {

    Physics::Update(deltaTime);
    player.Update(deltaTime);
    camera.position = player.position;


}

void Render(Renderer& renderer) {

    map.Draw(renderer);
    //functia draw din clasa render care primeste o variabila numita texture de tip resources clasa declarata in resources.h
    //incarcata in functia begin a jocului, positia, si marimea
    player.Draw(renderer);

    Physics::DebugDraw(renderer); //for degubber

}
