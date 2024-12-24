#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2i target, float speed, float angle )
    : speed(speed)
{
    shape.setSize(sf::Vector2f(2.f, 100.f)); // Set bullet size
    shape.setFillColor(sf::Color::Cyan); // Bullet color
    
    shape.setOrigin(shape.getSize().x / 2 + 1, shape.getSize().y - 3);  // Center the origin of the bullet
    
    shape.setPosition(position); // Start position
    shape.setRotation(angle + 90);

    // Calculate direction vector from the player to the mouse
    sf::Vector2f direction(target.x - position.x, target.y - position.y);
    
    // Normalize the direction (so it's a unit vector)
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0) {
        direction /= magnitude;
    }

    velocity = direction * speed; // Set velocity based on direction and speed
}

void Bullet::update(float deltaTime)
{
    // Move the bullet based on its velocity
    shape.move(velocity * deltaTime);  // Bullet speed adjusted by deltaTime
}
