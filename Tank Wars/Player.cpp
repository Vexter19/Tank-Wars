#include "Player.h"


Player::Player(Vector2f pos, TankCharacteristic tank) :
    Tank(pos, tank.texturePath, tank.texRectBody, tank.texRectTurrel,
    tank.turrelCenterX, tank.diffTankTurrel, tank.maxSpeed,
    tank.speedOfRotation, tank.speedTurrel, tank.rechargeTime, tank.damage * PLAYER_COEFF,
    tank.name, tank.health * PLAYER_COEFF)
{
    this->level = tank.level;
    this->health = tank.health * PLAYER_COEFF;
}

void Player::update(double time, short int direction, short int rotation,
    std::list<GameObject*> &objects, std::list<Enemy*> &enemies,
    std::list<Bullet*> &bullets, std::list<Animation*> &anims)
{
    if (this->isAlive() == true) {
        // ������� �������� ������� ����.
        if (direction == -1) {
            rotation *= -1;
        }

        if ((direction != 0) || (rotation != 0)) {
            if (soundPlayerVehicle.getStatus() != SoundSource::Status::Playing) {
                soundPlayerIdle.pause();
                soundPlayerVehicle.play();
            }
        } else {
            soundPlayerVehicle.pause();
            if (soundPlayerIdle.getStatus() != SoundSource::Status::Playing) {
                soundPlayerIdle.play();
            }
        }
        
        Tank::update(time, direction, rotation, objects, bullets, anims);

        for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
            GameObject *obj = *it;
            while (checkCollision(obj) == true) {
                backToPrevPos(direction, rotation, 0.01);
                //Tank::update(time, -direction, -rotation, objects, bullets, anims);
            }
        }
    }
}

double Player::getReaminingTime()
{
    return remainingTime;
}

int Player::getHealth()
{
    return health;
}

void Player::setHealth(int health)
{
    this->health = health;
}

int Player::getLevel()
{
    return level;
}