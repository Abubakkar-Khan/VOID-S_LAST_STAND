#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

private:
	float totalTime;
	float switchTime;
	

public:
	sf::IntRect uvRect;


public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void update(int row, float deltaTime);
};

