#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>  // For atan2
#include "Collider.h"

class Entity
{
protected:
    bool dead;
    Collider collider;
    sf::RectangleShape body;

public:
    Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size); // Constructor
    virtual ~Entity() = default; 

    virtual void Draw(sf::RenderWindow& window);
    virtual bool isDead() const;
    virtual void setDead(bool die);
    void setPosition(float x, float y) { body.setPosition(x, y); }

    virtual Collider& GetCollider() { return collider; }
};


