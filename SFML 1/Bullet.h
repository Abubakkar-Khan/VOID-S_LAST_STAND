#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>  // For atan2

class Bullet
{
public:
    sf::RectangleShape shape;

    sf::Vector2f velocity;
    float speed;

    Bullet(sf::Vector2f position, sf::Vector2i target, float speed, float angle); // Constructor
    void update(float deltaTime); // Update bullet position
};
