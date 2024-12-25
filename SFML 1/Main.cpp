#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>  
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace std;

static const float VIEW_HEIGHT = 500;

static void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = window.getSize().x / window.getSize().y;
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/p3.png");

    Player player(&playerTexture, sf::Vector2u(1, 1), 0.20f);

    Enemy enemy1(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(500.0f, 200.0f));
    Enemy enemy2(nullptr, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 400.0f));

    float deltaTime = 0.0f;
    sf::Clock clock;

    window.setFramerateLimit(60);  // Limits FPS to 60

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
                ResizeView(window, view);
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                    printf(" %c", evnt.text.unicode);
                break;
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos, view);

        sf::Vector2i worldMousePosInt(static_cast<int>(worldMousePos.x), static_cast<int>(worldMousePos.y));


        player.Update(deltaTime, worldMousePosInt);

        enemy1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
        enemy2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
        
        view.setCenter(player.GetPosition());

        window.clear();
    
        // Draw the player
        player.Draw(window);

        enemy1.Draw(window);
        enemy2.Draw(window);

        window.setView(view);
        window.display();
    }

    return 0;
}
