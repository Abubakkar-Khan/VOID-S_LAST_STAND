#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Entity.h"

class Player : virtual public Entity
{
private:
	Animation animation;

	float health;

	unsigned int row;
	sf::Vector2f movement;

	float acceleration;
	float deceleration;	
	float maxSpeed;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health);
	void Update(float deltaTime, sf::Vector2i mousePos);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	
	void setHealth(float nHealth);

	sf::Vector2f GetSize() { return body.getSize(); }
	float GetHealth() const { return health; }
	
	void setDead(bool die) override;
};

