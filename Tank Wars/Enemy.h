#ifndef ENEMY_H
#define ENEMY_H
#include "Tank.h"
#include <cmath>
#include <iostream>

#define VISIBILITY 700
#define COS_10 0.98
#define COS_30 0.86

class Enemy :
    public Tank
{
private:
    Texture *texDynamicObjects;
    bool alert;
public:
    double direction, rotation;

    Enemy(Vector2f pos, Texture *texDynObjs, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel, int health,
        double rechargeTime, int damage, std::string name);
    void update(double time, Tank &player, std::list<Bullet*> &bullets,
        std::list<GameObject*> &objects, std::list<Animation*> &anims);
};

#endif // !ENEMY_H