#include "Bullet.h"



Bullet::Bullet(sf::Texture* texture, sf::Vector2f position, sf::Vector2i target, float speed, float life, float size)
    : speed(speed), collider(shape), age(0.0f), lifetime(life)
{
    dead = false;

    shape.setSize(sf::Vector2f(size, size)); // Set bullet size
    //shape.setFillColor(sf::Color::Yellow); // Bullet color

    shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);
    shape.setPosition(position);

    // Calculate direction vector from the bullet's position to the target (mouse position)
    sf::Vector2f direction(target.x - position.x, target.y - position.y);

    // Normalize the direction vector (so it's a unit vector)
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0) {
        direction /= magnitude; // Normalize direction
    }

    // Calculate the angle in radians and convert it to degrees
    float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f;  // atan2 returns the angle in radians

    shape.setRotation(angle); // Set the bullet's rotation based on the angle
    shape.setTexture(texture);
    velocity = direction * speed; // Set velocity based on the normalized direction and speed
}

void Bullet::update(float deltaTime)
{
    // Move the bullet based on its velocity
    shape.move(velocity * deltaTime);  // Bullet speed adjusted by deltaTime
    age += deltaTime;
}

void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(shape);  // Draw the bullet on the window
}

bool Bullet::isDead()
{
    if (age >= lifetime)
        dead = true;
    else
        dead = false;  // Bullet is still alive
    return dead;
}

void Bullet::setDead(bool die)
{
    dead = die;
}
