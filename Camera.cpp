//
// Created by Edy on 23/05/2025.
//
#include <iostream>
#include "Camera.h"
#include <iostream>

Camera::Camera(float zoomLevel)
    : zoomLevel(zoomLevel)
{
    //this->zoomLevel = zoomLevel; metoda mai putin eficinte, declar variabila zoomLevel inainte de codul executat in constructor
}

sf::View Camera::GetView(sf::Vector2u windowSize) {
    float aspect =static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);//width to height ration
    sf:: Vector2f size ;
    if (aspect<1.0f)
        size=sf::Vector2f(zoomLevel, zoomLevel/aspect );
    else
        size=sf::Vector2f(zoomLevel*aspect, zoomLevel);

    return sf::View(position, size);
    //face centrul ecranului in mijolc si nu in coltul din dreapta sus, view data type se ocupa de cum da display ecranu,
    //viewpointu ecranului este handled de view class
    //sf::View object, which SFML uses to define the visible area of the game world.
}


