#include "Enemy.h"


Enemy::Enemy(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel, int turrelCenterX,
    double maxSpeed, double speedOfRotation, double speedTurrel, int health) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX,
    maxSpeed, speedOfRotation, speedTurrel)
{
    this->health = 200;
}

void Enemy::update(double time, Tank &player)
{
    Tank::update(time, 0, 0);
    if (sqrt(sqr(player.getPos().x - position.x) +
        sqr(player.getPos().y - position.y)) < 700) {
        rotateTurrel((Vector2i)player.getPos());
    }
}