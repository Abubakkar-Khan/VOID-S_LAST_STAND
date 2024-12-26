#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>  
#include <cstdlib>  
#include <ctime>  
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace std;

static const float VIEW_HEIGHT = 500;
static const float SPAWN_INTERVAL = 3.0f;

static void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    ResizeView(window, view);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("textures/p3.png")) {
        cerr << "Error loading player texture!" << endl;
        return -1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("textures/alien.png")) {
        cerr << "Error loading enemy texture!" << endl;
        return -1;
    }

    Player player(&playerTexture, sf::Vector2u(1, 1), 0.20f);

    /*Enemy enemy1(&enemyTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(500.0f, 200.0f));
    Enemy enemy2(&enemyTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(200.0f, 400.0f));*/

    float deltaTime = 0.0f;
    sf::Clock clock;


    // Boundry Wall
    sf::FloatRect worldBounds(0, 0, window.getSize().x, window.getSize().y);
    sf::RectangleShape boundary(sf::Vector2f(worldBounds.width - 2, worldBounds.height));
    boundary.setPosition(worldBounds.left - 5, worldBounds.top);
    boundary.setOutlineColor(sf::Color::White);
    boundary.setOutlineThickness(2);
    boundary.setFillColor(sf::Color::Transparent);

    window.setFramerateLimit(60);  // Limits FPS to 60

    vector<Bullet*> bullets;
    vector<Enemy*> enemies;

    float spawnTimer = 0.0f;

    // Game loop
    while (window.isOpen()) {
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
        sf::Vector2f playerPos = player.GetPosition();


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bullets.push_back(new Bullet (player.GetPosition(), worldMousePosInt, 500.0));
        }

        for (auto& enemy : enemies)
            enemy->GetCollider().CheckCollision(player.GetCollider(), 0.0f);


        // Spawn new enemies after the interval
        spawnTimer += deltaTime;
        if (spawnTimer >= SPAWN_INTERVAL)
        {
            spawnTimer = 0.0f;

            float spawnX = (rand() % 2 == 0) ? -50.0f : window.getSize().x + 50.0f;
            float spawnY = (rand() % 2 == 0) ? -50.0f : window.getSize().y + 50.0f;

            spawnX += rand() % 100 - 50; // -50 to 49 random 
            spawnY += rand() % 100 - 50; 
            
            enemies.push_back(new Enemy(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(spawnX, spawnY) ) );
        }


        view.setCenter(player.GetPosition());

        

        // Player clamping (keep player inside world bounds)
        sf::Vector2f playerSize = player.GetSize();

        if (playerPos.x < worldBounds.left)
            player.setPosition(worldBounds.left, playerPos.y);

        if (playerPos.x + playerSize.x > worldBounds.left + worldBounds.width)
            player.setPosition(worldBounds.left + worldBounds.width - playerSize.x, playerPos.y);

        if (playerPos.y < worldBounds.top)
            player.setPosition(playerPos.x, worldBounds.top);

        if (playerPos.y + playerSize.y > worldBounds.top + worldBounds.height)
            player.setPosition(playerPos.x, worldBounds.top + worldBounds.height - playerSize.y);

        // Check Enemies-Enemies Collisions
        for (size_t i = 0; i < enemies.size(); ++i) {
            for (size_t j = i + 1; j < enemies.size(); ++j) {
                enemies[i]->GetCollider().CheckCollision(enemies[j]->GetCollider(), 0.0f)   ;
                    // collision
                
            }
        }

        window.clear();
        
        window.draw(boundary);
    
        // Draw the player
        player.Draw(window);

        for (auto bullet = bullets.begin(); bullet != bullets.end();) {
            bool hit = false;  // Flag to check if the bullet has hit any enemy

            // Check for bullet-enemy collisions
            for (auto& enemy : enemies) {
                if ((*bullet)->GetCollider().CheckCollision(enemy->GetCollider(), 2.5f)) {
                    cout << "Bullet hit enemy!" <<  endl;


                    // Delete the bullet
                    delete *bullet;  // Free memory
                    bullet = bullets.erase(bullet);  // Remove from vector and continue the loop
                    hit = true;  // Set flag to indicate bullet hit an enemy
                    break;  // Exit the inner loop after first collision
                }
            }

            // If the bullet wasn't hit by any enemy, just continue to the next bullet
            if (!hit) {
                (*bullet)->update(deltaTime);  // Update the bullet
                (*bullet)->Draw(window);  // Draw the bullet
                ++bullet;  // Move to next bullet
            }
        }


        for (auto& enemy : enemies)
            enemy->Update(playerPos, deltaTime);

        for (auto& enemy : enemies)
            enemy->Draw(window);

        window.setView(view);
        window.display();
    }

    return 0;
}
