#ifndef ENEMY_H
#define ENEMY_H
#include "Tank.h"
#include <cmath>


class Enemy :
    public Tank
{
private:
    Texture *texDynamicObjects;
public:
    Enemy(Vector2f pos, Texture *texDynObjs, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel, int health,
        double rechargeTime, int damage, std::string name);
    void update(double time, Tank &player, std::list<Bullet*> &bullets,
        std::list<GameObject*> &objects, std::list<Animation*> &anims);
    double direction, rotation;
};

#endif // !ENEMY_H