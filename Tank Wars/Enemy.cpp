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
    rotation = 0;
}

void Enemy::update(double time, Tank &player, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims)
{
    Vector2f vecPlayer; // Вектор между врагом и игроком
    vecPlayer.x = player.getPos().x - position.x;
    vecPlayer.y = player.getPos().y - position.y;
    if (vectorLength(vecPlayer) < VISIBILITY) {
        alert = true;
    } else {
        alert = false;
    }
    if (alert == false) {
        // Спокойное поведение врага
        direction = 1;
        Tank::update(time, direction, rotation, objects, bullets, anims);
    } else {
        // Враг видит игрока
        
        if (player.isAlive()) {
            direction = 0;

            double scalar;

            // Поворот корпуса лбом к игроку
            scalar = scalarProd(normalizeVector(vecPlayer),
                Vector2f(cos(angle * PI / 180), sin(angle * PI / 180)));

            double dirPlayer = (180 / PI * atan((player.getPos().y - position.y) /
                (player.getPos().x - position.x)));
            if (player.getPos().x < position.x) {
                dirPlayer += 180;
            } else if (player.getPos().y < position.y) {
                dirPlayer += 360;
            }

            if (dirPlayer >= 360) {
                dirPlayer -= 360;
            }

            double dirDiff = dirPlayer - angle;

            if (dirDiff > 1) {
                rotation = 1;
            } else if (dirDiff < -1) {
                rotation = -1;
            } else {
                rotation = 0;
            }

            std::cout << angle << "  " << dirPlayer << std::endl;

            if ((angle <= 361) && (angle >= 270)
                && (dirPlayer >= 0) && (dirPlayer <= 90)) {
                angle -= 360;
                rotation = 1;
            }

            if ((dirPlayer <= 361) && (dirPlayer >= 270)
                && (angle >= 0) && (angle <= 90)) {
                angle += 360;
                rotation = -1;
            }

            if (scalar > COS_30) {
                rotation = 0;
            }

            // Поворот башни на игрока
            rotateTurrel((Vector2i)player.getPos());

            /* Если угол между вектором направления башни врага
            и игроком меньше 10 градусов, то можно стрелять */
            scalar = scalarProd(normalizeVector(vecPlayer),
                Vector2f(cos(dirTurrel * PI / 180), sin(dirTurrel * PI / 180)));
            //std::cout << scalar << std::endl;
            //std::cout << vecPlayer.x << "  " << vecPlayer.y << std::endl;
            
            if (scalar > COS_10) {                                    
                fire(bullets, *texDynamicObjects);
            }


            Tank::update(time, direction, rotation, objects, bullets, anims);
            GameObject *objPlayer = &player;
            if (checkCollision(objPlayer) == true) {
                Tank::update(time, -direction, -rotation, objects, bullets, anims);
            }
        }
    }
}