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
    // Constructor
    HealthBar(float maxHealth, sf::Vector2f position, sf::Vector2f size);

    // Update the health value and the health bar foreground
    void Update(float currentHealth);

    // Draw the health bar to the window
    void Draw(sf::RenderWindow& window);

    // Set the position of the health bar (background and foreground)
    void setPosition(sf::Vector2f position);
};
