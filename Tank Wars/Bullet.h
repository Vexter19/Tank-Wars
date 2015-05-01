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
    int damage;
    Texture *texture;
public:
    Bullet(Vector2f pos, float angle, Texture *tex, IntRect rect, int damage);
    void update(double time, View &view, RenderWindow &window,
        std::list<GameObject*> &objects, std::list<Animation*> &anims);
    bool isAlive();
    void Destroy(std::list<Animation*> &anims);
    int getDmg();
};

#endif // !BULLET_H