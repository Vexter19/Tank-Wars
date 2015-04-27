#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Animation.h"

using namespace sf;

class Bullet :
    public GameObject
{
private:
    double dx, dy;
    bool life;
    Texture *texture;
public:
    Bullet(Vector2f pos, float angle, Texture *tex, IntRect rect);
    void update(double time, View &view, RenderWindow &window);
    bool isAlive();
    void Destroy(std::list<Animation*> &anims);
};

#endif // !BULLET_H