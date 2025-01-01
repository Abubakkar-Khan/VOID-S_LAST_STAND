#include "Enemy2.h"

Enemy2::Enemy2(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position, float health, float speed)
    : Enemy(texture, imageCount, switchTime, size, position, health, speed) {
    // Additional initialization specific to Enemy2, if needed
}
