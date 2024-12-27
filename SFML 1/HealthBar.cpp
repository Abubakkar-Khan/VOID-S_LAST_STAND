#include "HealthBar.h"

HealthBar::HealthBar(float maxHealth, sf::Vector2f position, sf::Vector2f size)
	: m_maxHealth(maxHealth), m_currentHealth(maxHealth), m_position(position), m_size(size)
{
	m_background.setSize(size);
	m_background.setPosition(position);
	m_background.setOutlineColor(sf::Color::White);
	m_background.setOutlineThickness(1);
	m_background.setFillColor(sf::Color::Transparent);

	m_health.setSize(sf::Vector2f(m_size.x, m_size.y));
	m_health.setPosition(position);
	m_health.setFillColor(sf::Color(255, 255, 255));
}

void HealthBar::Update(float currentHealth)
{
	m_currentHealth = currentHealth;

	float healthPercentage = currentHealth / m_maxHealth;

	m_health.setSize(sf::Vector2f(m_size.x * healthPercentage, m_size.y));
}	

void HealthBar::Draw(sf::RenderWindow& window) {
	window.draw(m_background);  
	window.draw(m_health);      
}

void HealthBar::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_background.setPosition(m_position);  // Update the background position
	m_health.setPosition(m_position);      // Update the health foreground position
}

