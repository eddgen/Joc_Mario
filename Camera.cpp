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

sf::Vector2f Camera::GetViewSize() {

    return viewSize;
}

sf::View Camera::GetView(sf::Vector2u windowSize) {
    float aspect =static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);//width to height ration

    if (aspect<1.0f)
        viewSize=sf::Vector2f(zoomLevel, zoomLevel/aspect );
    else
        viewSize=sf::Vector2f(zoomLevel*aspect, zoomLevel);

    return sf::View(position, viewSize);
    //face centrul ecranului in mijolc si nu in coltul din dreapta sus, view data type se ocupa de cum da display ecranu,
    //viewpointu ecranului este handled de view class
    //sf::View object, which SFML uses to define the visible area of the game world.
}

sf::View Camera::GetUIView() {

    float aspect=viewSize.x/viewSize.y;
    viewSize=sf::Vector2f(100.0f, 100.0f/aspect );
    return sf::View(sf::Vector2f(),viewSize);
}


