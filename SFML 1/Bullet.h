#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>  // For atan2
#include "Collider.h"

class Bullet
{
private:
    float lifetime;
    float age;
    bool dead;

    Collider collider;

public:
    sf::RectangleShape shape;

    sf::Vector2f velocity;
    float speed;

    Bullet(sf::Texture* texture, sf::Vector2f position, sf::Vector2i target, float speed, float life, float size); // Constructor
    void update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    bool isDead();
    void setDead(bool die);
    Collider& GetCollider() { return collider; }
};


