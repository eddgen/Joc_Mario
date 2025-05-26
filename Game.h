//
// Created by Edy on 23/05/2025.
//

#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include "Camera.h"
#include "Renderer.h"


extern Camera camera; //defineste obiect de tip camera undeva in program nu doar in fisierul acesta, si te lasa sa il folosesti in mai multe fisiere

void Begin(const sf::Window& window);

void Update(float deltaTime);

void Render(Renderer& render);





#endif //GAME_H
