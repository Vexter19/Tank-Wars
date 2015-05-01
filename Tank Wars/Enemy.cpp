#include "Enemy.h"


Enemy::Enemy(Vector2f pos, Texture *texDynObjs, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, int health,
    double rechargeTime, int damage, std::string name) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX, diffTankTurrel,
    maxSpeed, speedOfRotation, speedTurrel, rechargeTime, damage, name, health)
{
    this->texDynamicObjects = texDynObjs;
    this->health = 200;
    direction = 0;
    rotation = 1;
}

void Enemy::update(double time, Tank &player, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims)
{
    Tank::update(time, direction, rotation, objects, bullets, anims);

    GameObject *objPlayer = &player;
    if (checkCollision(objPlayer) == true) {
        Tank::update(time, -direction, -rotation, objects, bullets, anims);
    }
    
    if (sqrt(sqr(player.getPos().x - position.x) +
        sqr(player.getPos().y - position.y)) < 700) {
        if (player.isAlive()) {
            rotateTurrel((Vector2i)player.getPos());
            fire(bullets, *texDynamicObjects);
        }
    }
}