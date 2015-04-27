#include "Enemy.h"


Enemy::Enemy(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, int health, double rechargeTime) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX, diffTankTurrel,
    maxSpeed, speedOfRotation, speedTurrel, rechargeTime)
{
    this->health = 200;
}

void Enemy::update(double time, Tank &player,
    std::list<Bullet*> &bullets, std::list<Animation*> &anims)
{
    Tank::update(time, 0, 0, bullets, anims);
    if (sqrt(sqr(player.getPos().x - position.x) +
        sqr(player.getPos().y - position.y)) < 700) {
        rotateTurrel((Vector2i)player.getPos());
    }
}