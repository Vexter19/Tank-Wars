#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"
#include "Enemy.h"


class Player :
    public Tank
{
public:
    Player(Vector2f pos, TankCharacteristic tank);

    void update(double time, short int direction, short int rotation,
        std::list<GameObject*> &objects, std::list<Enemy*> &enemies,
        std::list<Bullet*> &bullets, std::list<Animation*> &anims);

    double getReaminingTime();
    int getHealth();
};

#endif // !PLAYER_H