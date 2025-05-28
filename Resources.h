//
// Created by Edy on 24/05/2025.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include <unordered_map> // mai eficinet ca map care e by default ordered, si nu am nevoie de texturi in ordine
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>

class Resources {

    public:
    static std::unordered_map<std::string, sf::Texture> textures; //    static std::unordered_map<std::string, sf::Texture> textures; //
    static std::unordered_map<std::string,sf::SoundBuffer> sounds;
};



#endif //RESOURCES_H
