#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
private:
	sf::RectangleShape body;
	Animation animation;

	unsigned int row;
	float speed;

public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow window);


};

