#pragma once

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Collider.h"
#include "Animation.h"
#include "Entity.h"

class Enemy2 : public Enemy
{
public:
	Enemy2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position, float health, float speed);

};

