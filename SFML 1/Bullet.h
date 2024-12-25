#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>  // For atan2

class Bullet
{
private:
    float lifetime = 3.0f;  // Bullet lifetime in seconds
    float age = 0.0f;

public:
    sf::RectangleShape shape;

    sf::Vector2f velocity;
    float speed;

    Bullet(sf::Vector2f position, sf::Vector2i target, float speed); // Constructor
    void update(float deltaTime); // Update bullet position
    void Draw(sf::RenderWindow& window);

    bool isDead() const;
};
