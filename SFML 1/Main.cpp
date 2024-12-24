#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>  
#include "Player.h"
#include "Bullet.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0, 512.0));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/ship.png");

    Player player(&playerTexture, sf::Vector2u(5, 2), 0.03f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    window.setFramerateLimit(60);  // Limits FPS to 60

    //sf::Vector2f velocity(0.0f, 0.0f);  // Velocity vector
    //float acceleration = 2.2f;  // How fast the player accelerates
    //float deceleration = 0.98f;  // How fast the player slows down when no key is pressed
    //float maxSpeed = 8.0f;  // Maximum speed of the player

    std::vector<Bullet> bullets;
    
    
    while (window.isOpen()) {
        // Inside game loop

        deltaTime = clock.restart().asSeconds(); // Use seconds

        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                cout << "New Window Width: " << evnt.size.width << "\nNew Window Height: " << evnt.size.height << endl << endl;
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                    printf(" %c", evnt.text.unicode);
                break;
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        player.Update(deltaTime, mousePos);

        window.clear();

        ////////////////////////////////////////////////////////////////////////////////////////
        // Player Direction and Rotation
        /////////////////////////////////////////////////////////////////////////////////////////

        

        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //    bullets.emplace_back(playerPos, mousePos, 1600.f, angle);
        //}

        //// Update and draw bullets
        //for (auto& bullet : bullets) {
        //    bullet.update(deltaTime);
        //    window.draw(bullet.shape);
        //}

        // Draw the player
        player.Draw(window);
        window.display();
    }

    return 0;
}
