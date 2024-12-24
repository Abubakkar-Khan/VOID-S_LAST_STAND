#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>  // For atan2
#include "Animation.h"
#include "Bullet.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(512.0, 512.0));

    sf::RectangleShape player(sf::Vector2f(25, 40));


    player.setFillColor(sf::Color::White);
    player.setOrigin(12.5, 20);  // Set the origin to the center of the player

    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/ship.png");
    player.setTexture(&playerTexture);
    player.setPosition(206.0f, 206.0f);  // Start in the center of the window

    Animation animation(&playerTexture, sf::Vector2u(5, 2), 0.03f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    window.setFramerateLimit(60);  // Limits FPS to 60

    sf::Vector2f velocity(0.0f, 0.0f);  // Velocity vector
    float acceleration = 0.2f;  // How fast the player accelerates
    float deceleration = 0.98f;  // How fast the player slows down when no key is pressed
    float maxSpeed = 8.0f;  // Maximum speed of the player

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

        animation.update(2, deltaTime);
        player.setTextureRect(animation.uvRect);

        window.clear();

        ////////////////////////////////////////////////////////////////////////////////////////
        // Player Direction and Rotation
        /////////////////////////////////////////////////////////////////////////////////////////

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f playerPos = player.getPosition();

        // Calculate the direction vector from the player to the mouse
        sf::Vector2f direction(mousePos.x - playerPos.x, mousePos.y - playerPos.y);

        // Calculate the angle using atan2 (angle in radians)
        float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;  // Convert radians to degrees

        // Set the rotation of the player to the calculated angle
        player.setRotation(angle + 90); // + 90 for right angle

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            bullets.emplace_back(playerPos, mousePos, 1600.f, angle);
        }

        // Update and draw bullets
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
            window.draw(bullet.shape);
        }

        // Player movement controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            velocity.y -= acceleration;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            velocity.x -= acceleration;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            velocity.y += acceleration;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            velocity.x += acceleration;

        // Apply deceleration if no key is pressed
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            velocity.y *= deceleration;

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            velocity.x *= deceleration;

        // Cap the speed to prevent going too fast
        if (abs(velocity.x) > maxSpeed) velocity.x = maxSpeed * (velocity.x / abs(velocity.x));
        if (abs(velocity.y) > maxSpeed) velocity.y = maxSpeed * (velocity.y / abs(velocity.y));

        // Move the player with the velocity
        player.move(velocity);

        // Draw the player
        window.draw(player);
        window.display();
    }

    return 0;
}
