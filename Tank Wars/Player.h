#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"
#include "Enemy.h"


class Player :
    public Tank
{
private:
    int health;
    
public:
    Player(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel, int health);
    void update(double time, short int direction, short int rotation, std::list<Enemy*> &enemies);
};

#endif // !PLAYER_H