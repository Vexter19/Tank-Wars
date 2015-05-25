#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"
#include "Enemy.h"


class Player :
    public Tank
{
private:
    int level;
public:
    Player(Vector2f pos, TankCharacteristic tank);

    void update(double time, short int direction, short int rotation,
        std::list<GameObject*> &objects, std::list<Enemy*> &enemies,
        std::list<Bullet*> &bullets, std::list<Animation*> &anims);

    double getReaminingTime();
    int getHealth();
    void setHealth(int health);
    int getLevel();
};

#endif // !PLAYER_H