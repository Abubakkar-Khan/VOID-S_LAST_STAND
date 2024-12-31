#include "Entity.h"


Entity::Entity(sf::Texture* texture, sf::Vector2f position, sf::Vector2f size)
    : collider(body)
{
    dead = false;
    
    body.setSize(size); 

    body.setOrigin(body.getSize().x / 2.f, body.getSize().y / 2.f);
    body.setPosition(position);

    body.setTexture(texture);
}

void Entity::Draw(sf::RenderWindow& window)
{
    window.draw(body); 
}

bool Entity::isDead() const
{
    return dead;
}

void Entity::setDead(bool die)
{
    dead = die;
}



