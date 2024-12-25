#include "Collider.h"
#include <iostream>

Collider::Collider(sf::RectangleShape& body) : body(body) {}

//bool Collider::CheckCollision(Collider& other, float push)
//{
//    sf::Vector2f otherPosition = other.GetPosition();
//    sf::Vector2f otherHalfSize = other.GetHalfSize();
//    sf::Vector2f thisPosition = GetPosition();
//    sf::Vector2f thisHalfSize = GetHalfSize();
//    
//    float deltaX = otherPosition.x - thisPosition.x;
//    float deltaY = otherPosition.y - thisPosition.y;
//    
//    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
//    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
//    
//    if (intersectX < 0.0f && intersectY < 0.0f)
//    {
//        push = std::min (std::max (push, 0.0f), 1.0f);
//        
//        if (intersectX > intersectY)
//        {
//            if (deltaX > 0.0f)
//            {
//                Move(intersectX * (1.0f - push), 0.0f);
//                other.Move(-intersectX * push, 0.0f);
//            }
//            else
//            {
//                Move(-intersectX * (1.0f - push), 0.0f);
//                other.Move(intersectX * push, 0.0f);
//            }
//        }
//        else
//        {
//            if (deltaY > 0.0f)
//            {
//                Move(0.0f, intersectY * (1.0f - push));
//                other.Move(0.0f, -intersectY * push);
//            }
//            else
//            {
//                Move(0.0f, -intersectY * (1.0f - push));
//                other.Move(0.0f, intersectY * push);
//            }
//        }
//        
//        return true;
//    } 
//      
//    return false;
//}



//bool Collider::CheckCollision(const Collider& other, float push) {
//    sf::FloatRect thisBounds = body.getGlobalBounds();
//    sf::FloatRect otherBounds = other.body.getGlobalBounds();
//    if (thisBounds.intersects(otherBounds))
//    {
//        std::cout << "\nCollided\n";
//        return true;
//    }
//}

bool Collider::CheckCollision(Collider& other, float push)
{
    // Get the positions and half-sizes of both colliders (player and enemy)
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    // Calculate the difference in position between the two colliders
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    // Calculate how much the bounding boxes overlap in the X and Y directions
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    // Check if the objects are intersecting (i.e., the overlap is negative)
    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        // Clamp the push factor between 0 and 1
        push = std::min(std::max(push, 0.0f), 1.0f);

        // Resolve collision by moving the objects apart
        if (intersectX > intersectY)
        {
            // Horizontal collision
            if (deltaX > 0.0f)
            {
                // Move the current object to the right, and the other to the left
                Move(intersectX * (1.0f - push), 0.0f);
                other.Move(-intersectX * push, 0.0f);
            }
            else
            {
                // Move the current object to the left, and the other to the right
                Move(-intersectX * (1.0f - push), 0.0f);
                other.Move(intersectX * push, 0.0f);
            }
        }
        else
        {
            // Vertical collision
            if (deltaY > 0.0f)
            {
                // Move the current object down, and the other object up
                Move(0.0f, intersectY * (1.0f - push));
                other.Move(0.0f, -intersectY * push);
            }
            else
            {
                // Move the current object up, and the other object down
                Move(0.0f, -intersectY * (1.0f - push));
                other.Move(0.0f, intersectY * push);
            }
        }

        // Return true to indicate a collision occurred
        return true;
    }

    // No collision detected
    return false;
}


