#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>  // For atan2
#include "Collider.h"
#include "Entity.h"


class Bullet : Entity
{
private:
    float lifetime;
    float age;


    sf::Vector2f velocity;
    float speed;

public:

    Bullet(sf::Texture* texture, sf::Vector2f position, sf::Vector2i target, float speed, float life, sf::Vector2f size); // Constructor
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    bool isDead();
    void setDead(bool die);
};


