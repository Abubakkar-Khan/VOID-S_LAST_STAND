#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include "Entity.h"
#include "Entity.h"

class Enemy : virtual public Entity
{
private:
	Animation animation;

	float health;
	unsigned int row;
	float speed;


public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position, float health, float speed);
	
	void Update(sf::Vector2f playerPos, float daltaTime);

	sf::Vector2f getPosition() { return body.getPosition(); }

	void setDead(bool die) override;
};

















