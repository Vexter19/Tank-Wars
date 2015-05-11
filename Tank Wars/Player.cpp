#include "Player.h"


Player::Player(Vector2f pos, TankCharacteristic tank) :
    Tank(pos, tank.texturePath, tank.texRectBody, tank.texRectTurrel,
    tank.turrelCenterX, tank.diffTankTurrel, tank.maxSpeed,
    tank.speedOfRotation, tank.speedTurrel, tank.rechargeTime, tank.damage,
    tank.name, tank.health)
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