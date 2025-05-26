//
// Created by Edy on 23/05/2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Camera {
    public:
    Camera(float zoomLevel = 5.0f); //constructor pt clasa Camera
    sf::View GetView(sf::Vector2u windowSize); // declararea functiei GetView

    float zoomLevel;
    sf::Vector2f position;
};



#endif //CAMERA_H
