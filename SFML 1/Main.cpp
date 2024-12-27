#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>  
#include <cstdlib>  
#include <ctime>  
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "HealthBar.h"

using namespace std;

const float MAX_PLAYER_HEALTH = 100.0f;
const float ENEMY_HEALTH = 2.0f;

sf::Vector2f WORLD_SIZE(1500.0f, 1500.0f);

static const float VIEW_HEIGHT = 512;
float SPAWN_INTERVAL = 2.0f;
float BULLET_INTERVAL = 0.2f;

static void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML Tutorial", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture cursorTexture;
    if (!cursorTexture.loadFromFile("textures/11.png")) {
        cerr << "Error loading cursor texture!" << endl;
        return -1;
    }

    window.setMouseCursorVisible(false);

    sf::Sprite cursorSprite(cursorTexture);
    cursorSprite.setOrigin(cursorTexture.getSize().x / 2.0f, cursorTexture.getSize().y / 2.0f);
    cursorSprite.setScale(0.5f, 0.5f);
    
    srand(static_cast<unsigned int>(time(0)));

    sf::Text timerText;
    sf::Text scoreText;
    sf::Font font;
    if (!font.loadFromFile("Fonts/V.ttf")) {
        cerr << "Error loading font!" << endl;
        return -1;
    }

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);

    sf::Text healthLabel;
    healthLabel.setFont(font);
    healthLabel.setCharacterSize(20);
    healthLabel.setFillColor(sf::Color::White);
    healthLabel.setString("Health");
    
    sf::Text scoreLabel;
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(20);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setString("Score");
    scoreLabel.setOrigin(scoreLabel.getLocalBounds().width / 2, scoreLabel.getLocalBounds().height / 2);
    
    int score = 0;
    

    // First call for consisten
    ResizeView(window, view);
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Bullet Sound
    sf::SoundBuffer bulletSoundBuffer;
    if (!bulletSoundBuffer.loadFromFile("Sounds/laser.wav"))
    {
        cerr << "Error loading bullet sound!" << endl;
        return -1;
    }
    
    sf::Sound bulletSound;
    bulletSound.setBuffer(bulletSoundBuffer);

    sf::SoundBuffer enemySoundBuffer;
    if (!enemySoundBuffer.loadFromFile("Sounds/laser.wav"))
    {
        cerr << "Error loading bullet sound!" << endl;
        return -1;
    }
    
    sf::Sound enemySound;
    enemySound.setBuffer(enemySoundBuffer);




    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Player
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

    Player player(&playerTexture, sf::Vector2u(1, 1), 0.20f, MAX_PLAYER_HEALTH);

    float deltaTime = 0.0f;
    sf::Clock clock;

    // Boundry Wall
    sf::FloatRect worldBounds(0, 0, WORLD_SIZE.x, WORLD_SIZE.y);
    sf::RectangleShape boundary(sf::Vector2f(worldBounds.width - 2, worldBounds.height));
    boundary.setPosition(worldBounds.left - 5, worldBounds.top - 5);
    boundary.setOutlineColor(sf::Color(100, 200, 200));
    boundary.setOutlineThickness(2);
    boundary.setFillColor(sf::Color::Transparent);



    window.setFramerateLimit(60);  // Limits FPS to 60

    vector<Bullet*> bullets;
    vector<Enemy*> enemies;

    float spawnTimer = 0.0f;
    float bulletTimer = 0.0f;

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    // Game loop
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds(); // Use seconds
        static float elapsedTime = 0;
        elapsedTime += deltaTime;
        
        if (SPAWN_INTERVAL > 1.0f)
            SPAWN_INTERVAL -= deltaTime * deltaTime;
        else
            SPAWN_INTERVAL = 1.0f;

        int minutes = static_cast<int>(elapsedTime) / 60;
        int seconds = static_cast<int>(elapsedTime) % 60;

        string timeString = (minutes < 10 ? "0" : "") + to_string(minutes) + ":"
            + (seconds < 10 ? "0" : "") + to_string(seconds);

        timerText.setString(timeString);




        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                cout << window.getSize().x << ":" << window.getSize().y << endl;
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


        ////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////

        // Spawn new enemies after the interval
        spawnTimer += deltaTime;
        if (spawnTimer >= SPAWN_INTERVAL)
        {
            spawnTimer = 0.0f;

            float spawnX = (rand() % 2 == 0) ? -50.0f : window.getSize().x + 50.0f;
            float spawnY = (rand() % 2 == 0) ? -50.0f : window.getSize().y + 50.0f;

            spawnX += rand() % 100 - 50; // -50 to 49 random 
            spawnY += rand() % 100 - 50; 
            
            enemies.push_back(new Enemy(nullptr, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(spawnX, spawnY), ENEMY_HEALTH ));
        }

        bulletTimer += deltaTime;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bulletTimer >= BULLET_INTERVAL)
        {
            bullets.push_back(new Bullet (player.GetPosition(), worldMousePosInt, 800.0));
            bulletSound.play();
            bulletTimer = 0;
        }

        
        for (auto& enemy : enemies) {
            if(enemy->GetCollider().CheckCollision(player.GetCollider(), 0.0f))
            {
                player.setDead(true);
            }
        }
        
        view.setCenter(player.GetPosition());
        

        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////

        // UI / UX
        timerText.setPosition(player.GetPosition().x , player.GetPosition().y - view.getSize().y / 2.2); 
        timerText.setOrigin(timerText.getLocalBounds().width / 2, timerText.getLocalBounds().height / 2);  // Set origin to the center of the text

        HealthBar healthBar(MAX_PLAYER_HEALTH, sf::Vector2f(player.GetPosition().x - view.getSize().x / 2.2, player.GetPosition().y - view.getSize().y / 2.3), sf::Vector2f(150.0f, 5.0f));
        scoreText.setPosition(player.GetPosition().x + view.getSize().x / 3, player.GetPosition().y - view.getSize().y / 2.3);
        healthLabel.setPosition(player.GetPosition().x - view.getSize().x / 2.6, player.GetPosition().y - view.getSize().y / 2.1f);
        scoreLabel.setPosition(player.GetPosition().x + view.getSize().x / 2.85, player.GetPosition().y - view.getSize().y / 2.1f);

        timerText.setOrigin(timerText.getLocalBounds().width / 2, timerText.getLocalBounds().height / 2);
        scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
        healthLabel.setOrigin(healthLabel.getLocalBounds().width / 2, healthLabel.getLocalBounds().height / 2);
        
        healthBar.Update(player.GetHealth());
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Player clamping (keep player inside world bounds)
        sf::Vector2f playerSize = player.GetSize();

        if (playerPos.x < worldBounds.left)
            playerPos.x = worldBounds.left;

        if (playerPos.x + playerSize.x > worldBounds.width)
            playerPos.x = worldBounds.width - playerSize.x;

        if (playerPos.y < worldBounds.top)
            playerPos.y = worldBounds.top;

        if (playerPos.y + playerSize.y >  worldBounds.height)
            playerPos.y = worldBounds.height - playerSize.y;

        player.setPosition(playerPos.x, playerPos.y);


        /////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////

        // Check Enemies-Enemies Collisions
        for (size_t i = 0; i < enemies.size(); ++i) 
            for (size_t j = i + 1; j < enemies.size(); ++j) 
                enemies[i]->GetCollider().CheckCollision(enemies[j]->GetCollider(), 0.0f)   ;
            

        cursorSprite.setPosition(worldMousePos);

        window.clear();
        
        window.draw(boundary);
    
        // Draw the player
        player.Draw(window);

        for (auto bullet = bullets.begin(); bullet != bullets.end();) {
            bool hit = false; 

            // Check for bullet-enemy collisions
            for (auto& enemy : enemies) {
                if ((*bullet)->GetCollider().CheckCollision(enemy->GetCollider(), 2.5f)) {
                    enemy->setDead(true);
                    score++;
                    cout << "Score :" << score << endl;
                    // Increment Score

                    // Delete the bullet
                    delete *bullet;  // Free memory
                    bullet = bullets.erase(bullet); 
                    hit = true; 
                    break;
                }
            }

            window.draw(cursorSprite);

            for (auto enemy = enemies.begin(); enemy != enemies.end(); )
            {
                if ( (*enemy)->isDead() )
                {
                    delete* enemy;
                    enemySound.play();

                    enemy = enemies.erase(enemy);
                }
                else
                {
                    enemy++;
                }
            }

            // If the bullet wasn't hit by any enemy, just continue to the next bullet
            if (!hit) {
                (*bullet)->update(deltaTime);  // Update the bullet
                (*bullet)->Draw(window);  // Draw the bullet
                ++bullet;  // Move to next bullet
            }
        }

        string scoreString = to_string(score);
        scoreText.setString(scoreString);


        window.draw(timerText);
        window.draw(scoreText);
        window.draw(healthLabel);
        window.draw(scoreLabel);
        healthBar.Draw(window);


        for (auto& enemy : enemies)
            enemy->Update(playerPos, deltaTime);

        for (auto& enemy : enemies)
            enemy->Draw(window);

        window.setView(view);
        window.display();
    }

    return 0;
}
