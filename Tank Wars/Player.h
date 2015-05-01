#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"
#include "Enemy.h"


class Player :
    public Tank
{
public:
    Player(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel, int health,
        double rechargeTime, int damage, std::string name);
    void update(double time, short int direction, short int rotation,
        std::list<GameObject*> &objects, std::list<Enemy*> &enemies,
        std::list<Bullet*> &bullets, std::list<Animation*> &anims);
    double getReaminingTime();
};

#endif // !PLAYER_H