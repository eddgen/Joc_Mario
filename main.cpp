#include <SFML/Graphics.hpp>
#include  "Game.h"
#include "Camera.h"
#include  "Renderer.h"
#include <iostream>
#include "Player.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 900), "Mario but BETTER");
    window.setFramerateLimit(120);

    sf::Clock deltaClock; //pt a nu fi diferente intre 2 tipuri de computere


    Renderer renderer(window);



    Begin(window);
    while (window.isOpen())
    { //loop care tine fereastra, cat timp este deschisa se tot rescrie

        float deltaTime = deltaClock.restart().asSeconds(); //timpu pe care il ia un frame ca se se intaple

        sf::Event event{}; //pt a face fereastra respoinsive la anumite eventuri
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) // close the window when pressing esc
                //window.close(); // adauga window de confirmare
                paused=!paused;
        }

        Update(deltaTime);

        window.clear();

        window.setView(camera.GetView(window.getSize()));
        Render(renderer);

        window.setView(camera.GetUIView());
        RenderUI(renderer);

        window.display();

    }

    return 0;
}



























/*#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

using namespace sf;

int main() {

    RenderWindow window(VideoMode(512, 512), "Window", Style::Close | Style::Titlebar | Style::Resize);
    Texture playerTexture;

    playerTexture.loadFromFile("../poze/tux.png"); //../ a folder up si /folder_nume/ un folder down

    //obiect player
    Player player(&playerTexture, Vector2u(3,10),0.2f, 100.0f);


    float deltaTime=0.0f;
    Clock clock;

    // Vector2u textureSize = playerTexture.getSize();

    /*textureSize.y/=2;

    player.setTextureRect(IntRect(0, textureSize.y*1, textureSize.x, textureSize.y));
    #1#

    // player.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));

    while (window.isOpen())
    {
        deltaTime=clock.restart().asSeconds();

        sf::Event evnt;

        while (window.pollEvent(evnt))
        {
            switch (evnt.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::Resized:
                    std:: cout << "New window width: " <<  evnt.size.width << "   New window height: " << evnt.size.height << std::endl;
                    break;
                case Event::TextEntered:
                    if (evnt.text.unicode <128){
                        printf("%c",evnt.text.unicode);
                    }
                    break;
            }
        }

         /*
         //keyboard player movement

        if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
            player.move(-0.1f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
            player.move(0.1f, 0.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
            player.move(0.0f, -0.1f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
            player.move(0.0f, 0.1f);
        }

       //  mouse player movement
        if (Mouse::isButtonPressed(Mouse::Left)) {

            Vector2i mousepos= Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousepos.x), static_cast<float>(mousepos.y));
        }
        #1#


        player.Update(deltaTime); //the goat


        window.clear(Color(150,150,150));
        player.Draw(window);
        window.display();
    }



    return 0;
}*/