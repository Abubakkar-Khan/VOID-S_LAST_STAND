#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Enemy
{
private:
	sf::RectangleShape body;

public:
	Enemy(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	 
	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
};

