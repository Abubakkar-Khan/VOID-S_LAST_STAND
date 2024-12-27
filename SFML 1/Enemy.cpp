#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, float health) : collider(body), health(health)
{
    dead = false;

    body.setSize(size);
    body.setOrigin(size / 2.0f);  // Set origin to the center
    body.setTexture(texture);
    body.setPosition(position);
    body.setFillColor(sf::Color(250, 50, 50));
}

void Enemy::Draw(sf::RenderWindow& window)
{
    window.draw(body);  // Draw the enemy to the screen
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

    // Move the enemy towards the player
    float speed = 100.f;  // Speed of the enemy
    body.move(direction * speed * daltaTime);  // Move with a multiplier to adjust speed
}


bool Enemy::isDead() const
{
    return dead;
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
