#ifndef ENEMY_H
#define ENEMY_H
#include "Tank.h"
#include <cmath>


class Enemy :
    public Tank
{
private:
    int health;
public:
    Enemy(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel, int turrelCenterX,
        double maxSpeed, double speedOfRotation, double speedTurrel, int health);
    void update(double time, Tank &player);
};

#endif // !ENEMY_H