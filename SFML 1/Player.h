#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
private:
	sf::RectangleShape body;
	Animation animation;

	bool dead;
	float health;

	unsigned int row;
	sf::Vector2f movement;

	float acceleration;
	float deceleration;	
	float maxSpeed;

	Collider collider;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health);
	void Update(float deltaTime, sf::Vector2i mousePos);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	void setPosition(float x, float y) { body.setPosition(x, y); }
	sf::Vector2f GetSize() { return body.getSize(); }
	float GetHealth() const { return health; }
	
	bool isDead() const;
	void setDead(bool die);


	Collider& GetCollider() { return collider; }
};

