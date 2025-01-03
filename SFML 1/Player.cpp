#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health) :
    Entity(texture, body.getPosition(), { 40.0f, 40.0f }), animation(texture, imageCount, switchTime), movement(0.0f, 0.0f), health(health)
{
	row = 1;

    acceleration = 20.0f;  
    deceleration = 0.98f; 
    maxSpeed = 8.0f;  
    
    //body.setFillColor(sf::Color(150, 250, 255));

}

void Player::Update(float deltaTime, sf::Vector2i mousePos)
{
    // Movement based on key presses
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        movement.y -= acceleration * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        movement.x -= acceleration * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y += acceleration * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x += acceleration * deltaTime;

    // Apply deceleration if no key is pressed (smooth deceleration)
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        movement.y *= deceleration;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        movement.x *= deceleration;

    // Cap the speed to prevent going too fast
    if (abs(movement.x) > maxSpeed) movement.x = maxSpeed * (movement.x / abs(movement.x));
    if (abs(movement.y) > maxSpeed) movement.y = maxSpeed * (movement.y / abs(movement.y));

    sf::Vector2f playerPos = body.getPosition();

    // Calculate the direction vector from the player to the mouse
    sf::Vector2f direction(mousePos.x - playerPos.x, mousePos.y - playerPos.y);

    // Normalize the direction vector for consistent speed
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    // Calculate the angle using atan2 (angle in radians)
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159f;  // Convert radians to degrees

    body.setRotation(angle + 90); // + 90 for right angle

    animation.update(row, deltaTime);

    // Apply movement and update the player position
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}


void Player::setHealth(float nHealth)
{
    health = nHealth;
}

void Player::setDead(bool die)
{
    
    if (die) {
        if (health != 0)
            health--;
        std::cout << "! Player Health: " << health << std::endl;
    }

    if (health <= 0)
    {
        dead = true; 
        std::cout << "Player is DEAD: "<< std::endl;
        std::cout << "GAME OVER: "<< std::endl;
    }
    if (!die)
    {
        dead = false;
    }
}



