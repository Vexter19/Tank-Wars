#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
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
    void update(double time, View &view, RenderWindow &window,
        Player &player, std::list<Enemy*> &enemies, std::list<Animation*> &anims);
    bool isAlive();
};

#endif // !BULLET_H