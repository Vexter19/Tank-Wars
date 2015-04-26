#include "Player.h"


Player::Player(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, int health) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX, diffTankTurrel,
    maxSpeed, speedOfRotation, speedTurrel)
{
    
    this->health = health;
}



void Player::update(double time, short int direction, short int rotation, std::list<Enemy*> &enemies)
{
    Tank::update(time, direction, rotation);
    for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        GameObject *obj = *it;
        while (checkCollision(obj) == true) {
            Tank::update(time, -direction, -rotation);
        }
    }
}