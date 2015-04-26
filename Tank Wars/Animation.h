#ifndef ANIMATION_H
#define ANIMATION_H
#include "GameObject.h"


class Animation :
    public GameObject
{
private:
    int countOfFrames;
    double currentFrame;
    bool isCycled;
    IntRect firstRect;
public:
    Animation(Texture &tex, int countOfFrames, bool isCycled, IntRect frameRect, Vector2f pos);
    void update(double time);
    bool isAlive();
};

#endif // !ANIMATION_H