#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Enemy
{
private:
	sf::RectangleShape body;
	Collider collider;

	bool dead;
	float health;

public:
	Enemy(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, float health);
	 
	void Draw(sf::RenderWindow& window);
	
	void Update(sf::Vector2f playerPos, float daltaTime);

	Collider& GetCollider() { return collider; }

	bool isDead() const;
	void setDead(bool die);
};

