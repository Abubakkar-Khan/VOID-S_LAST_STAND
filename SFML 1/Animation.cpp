#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(int row, float deltaTime)
{
    // Ensure the animation row is correctly set
    currentImage.y = row;
    totalTime += deltaTime;

    // Update the current column index based on elapsed time
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++; // Move to the next frame (column)
        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0; // Loop back to the first frame
        }
    }

    // Set the texture rectangle to display the correct frame
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
