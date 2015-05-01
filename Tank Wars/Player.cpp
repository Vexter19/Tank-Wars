#include "Player.h"


Player::Player(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, int health,
    double rechargeTime, int damage, std::string name) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX, diffTankTurrel,
    maxSpeed, speedOfRotation, speedTurrel, rechargeTime, damage, name, health)
{
    
    this->health = health;
}



void Player::update(double time, short int direction, short int rotation,
    std::list<GameObject*> &objects, std::list<Enemy*> &enemies,
    std::list<Bullet*> &bullets, std::list<Animation*> &anims)
{
    // Убираем инверсию заднего хода.
    if (direction == -1) {
        rotation *= -1;
    }

    Tank::update(time, direction, rotation, objects, bullets, anims);

    for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        GameObject *obj = *it;
        while (checkCollision(obj) == true) {
            Tank::update(time, -direction, -rotation, objects, bullets, anims);
        }
    }
}

double Player::getReaminingTime()
{
    return remainingTime;
}