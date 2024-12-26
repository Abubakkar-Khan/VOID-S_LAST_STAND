#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
private:
	float m_maxHealth;
	float m_currentHealth;

	sf::Vector2f m_position;
	sf::Vector2f m_size;


	sf::RectangleShape m_background;
	sf::RectangleShape m_health; // Foreground

public:
	HealthBar(float maxHealth, sf::Vector2f position, sf::Vector2f size);

	void Update(float currentHealth);
	void Draw(sf::RenderWindow& window);
};

