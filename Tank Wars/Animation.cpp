#include "Animation.h"


void Animation::update(double time)
{
    if (currentFrame < countOfFrames) {
        IntRect currentRect = sprite.getTextureRect();
        sprite.setTextureRect(IntRect(firstRect.left + currentRect.width * (int)currentFrame,
            currentRect.top, currentRect.width, currentRect.height)); 
        currentFrame += currentFrame * time / 100;        
    }    
}

Animation::Animation(Texture &tex, int countOfFrames, bool isCycled, IntRect frameRect, Vector2f pos) :
GameObject(pos, tex, frameRect)
{
    this->countOfFrames = countOfFrames;
    this->currentFrame = 1;
    this->isCycled = isCycled;
    firstRect = frameRect;
    sprite.setPosition(position.x, position.y);
}

bool Animation::isAlive()
{
    if (!isCycled && (currentFrame < countOfFrames)) {
        return true;
    } else {
        return false;
    }
}