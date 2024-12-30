#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, 
    sf::Vector2f size, sf::Vector2f position, float health) : Entity(texture, position, size), animation(texture, imageCount, switchTime), health(health)
{
    row = 0;

    body.setFillColor(sf::Color(150, 250, 150));
}


void Enemy::Update(sf::Vector2f playerPos, float daltaTime)
{
    // Calculate direction vector from enemy to player
    sf::Vector2f direction = playerPos - body.getPosition();

    // Calculate magnitude (distance)
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0) {
        direction /= magnitude;  // Normalize the direction
    }
    animation.update(row, daltaTime);
    
    // Calculate the angle in radians and convert it to degrees
    float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f;  // atan2 returns the angle in radians
    
    body.setRotation(angle + 90);

    // Move the enemy towards the player
    float speed = 100.f;  // Speed of the enemy
    body.setTextureRect(animation.uvRect);
    body.move(direction * speed * daltaTime);  // Move with a multiplier to adjust speed
}

void Enemy::setDead(bool die) 
{
    if (die)
    {
        health--;
        std::cout << "Enemy Health: " << health << std::endl;
    }
    if (health <= 0)
        dead = true;
}
