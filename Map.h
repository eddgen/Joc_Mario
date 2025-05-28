//
// Created by Edy on 25/05/2025.
//

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include "Renderer.h"
#include <SFML/Graphics.hpp>

#include "Object.h"

class Map {

public:
    Map(float cellSize =32.0f);
    void CreateCheckerboard(size_t width, size_t height); //size_t = unsigned long long
    sf::Vector2f CreateFromImage(const sf::Image& image, std::vector<Object*>& objects);
    void Draw(Renderer& renderer) ;
    void InitFromImage();

    std::vector<std::vector<sf::Texture*>> grid; //two dimensional array type using 2 vestor type in c++
    float cellSize;
};



#endif //MAP_H
