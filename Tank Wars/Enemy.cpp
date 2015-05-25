#include "Enemy.h"


Enemy::Enemy(Vector2f pos, Texture *texDynObjs, TankCharacteristic tank) :
    Tank(pos, tank.texturePath, tank.texRectBody, tank.texRectTurrel,
    tank.turrelCenterX, tank.diffTankTurrel, tank.maxSpeed,
    tank.speedOfRotation, tank.speedTurrel, tank.rechargeTime, tank.damage,
    tank.name, tank.health)
{
    this->texDynamicObjects = texDynObjs;
    this->health = health;
    direction = 0;
    rotation = 0;
    IntRect temp = this->sprite.getTextureRect();
    bigSprite.setOrigin(temp.width / 2, temp.height / 2);
    temp.width *= 3;
    
    this->travelled = 0;
    distance = GO_DISTANCE;
    rotated = 0;

    // Убрать. Отображать текстуру направления танка
    bigSprite.setTexture(*texDynObjs);
    bigSprite.setTextureRect(temp);
    bigSprite.setColor(Color::Red);
}

void Enemy::update(double time, Tank &player, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims,
    std::list<Enemy*> &enemies)
{
    Vector2f vecPlayer; // Вектор между врагом и игроком
    vecPlayer.x = player.getPos().x - position.x;
    vecPlayer.y = player.getPos().y - position.y;
    if ((vectorLength(vecPlayer) < VISIBILITY) && (player.isAlive())) {
        alert = true;
    } else {
        alert = false;
    }

    bool willCollidedWithEnemy = false;
    for (std::list<Enemy*>::iterator it = enemies.begin();
        it != enemies.end(); ++it) {
        GameObject *obj = *it;
        if (*it != this) {
            if (checkCollision(obj)) {
                willCollidedWithEnemy = true;
            }
        }
    }

    if (alert == false) { // Если враг не видит игрока
        // TODO поворачиваем на случайный угол
        // пока не проехали нужное расстояние
        if (travelled < distance) {
            stopTimeGone = 0;
            travelled += 0.001;
            for (std::list<GameObject*>::iterator it = objects.begin();
                it != objects.end(); ++it) {

                GameObject *obj = *it;
                if (Collision::BoundingBoxTest(bigSprite, obj->getSprite()) ||
                    isOutOfMap() || willCollidedWithEnemy) {
                    // Если на пути есть объект или враг или скоро конец карты...
                    srand(time);
                    int randDir;
                    
                    // Случайно выбираем направление, в каком объезжать препятствие
                    if ((rand() % 2) == 0) {
                        randDir = -1;
                    } else {
                        randDir = 1;
                    }

                    // Сравниваем направление поворота с предыдущим.
                    // Если они одинаковые, то меняем направление.
                    if (prevRandDir == randDir) {
                        randDir *= -1;
                    }
                    prevRandDir = randDir;

                    double backupAngle = bigSprite.getRotation();

                    // Пробуем повернуться в одну сторону
                    bigSprite.setRotation(backupAngle + randDir * TRY_ROTATE_ANGLE);

                    // Если в этом направлении нет препятствий, то поворачиваемся так
                    if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())
                        == false && !isOutOfMap()) {
                        rotation = randDir;
                        break;
                    } else {
                        // Иначе пробуем повернуться в противоположном направлении
                        bigSprite.setRotation(backupAngle - randDir * TRY_ROTATE_ANGLE);

                        if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())
                            == false && !isOutOfMap()) {
                            rotation = randDir * -1;
                            break;
                        } else {
                            direction = -1;
                            rotation = randDir;
                        }
                    }
                } else {
                    // Если впереди чисто, просто едем вперёд
                    direction = 1;
                    rotation = 0;

                    // Сохраняем вектор направления
                    calmRotateTo1.x = this->getPos().x + 10 * cos(angle * PI / 180);
                    calmRotateTo1.y = this->getPos().y + 10 * sin(angle * PI / 180);
                }

                if (isOutOfMap()) {
                    direction = -1;
                }
            }

            rotateTurrel((Vector2i)calmRotateTo1);
        } else {

            // Как только прекратили движение, определяем направления,
            // в которых вращать башню во время остановки
            if (stopTimeGone == 0) {
                calmRotateTo1.x = this->getPos().x + 10 * cos((dirTurrel + 45) * PI / 180);
                calmRotateTo1.y = this->getPos().y + 10 * sin((dirTurrel + 45) * PI / 180);
                calmRotateAngle1 = dirTurrel + 45;
                calmRotateTo2.x = this->getPos().x + 10 * cos((dirTurrel - 45) * PI / 180);
                calmRotateTo2.y = this->getPos().y + 10 * sin((dirTurrel - 45) * PI / 180);
                calmRotateAngle2 = dirTurrel - 45;
                srand(time * 100);
                stopTime = RAND_STOP_TIME + (rand() % 6) - 3;
            }

            if (stopTimeGone < stopTime) {
                stopTimeGone += time / 1000;
                direction = 0;
                rotation = 0;

                if (rotated == 0) {
                    rotateTurrel((Vector2i)calmRotateTo1);
                    if ((dirTurrel < (calmRotateAngle1 + 5)) &&
                        (dirTurrel >(calmRotateAngle1 - 5))) {
                        rotated = 1;
                    }
                }

                if (rotated == 1) {
                    rotateTurrel((Vector2i)calmRotateTo2);
                }    
            } else {
                rotated = 0;
                travelled = 0;
                srand(time * 100);
                distance = GO_DISTANCE + (rand() % 10) - 5;
            }
        }
    } else {
        // Если враг видит игрока
        for (std::list<GameObject*>::iterator it = objects.begin();
            it != objects.end(); ++it) {

            GameObject *obj = *it;
            if (Collision::BoundingBoxTest(bigSprite, obj->getSprite()) ||
                willCollidedWithEnemy || isOutOfMap()) {
                // Если на пути есть объект
                double backupAngle = bigSprite.getRotation();
                bigSprite.setRotation(backupAngle + TRY_ROTATE_ANGLE);

                if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())) {
                    //bigSprite.setRotation(backupAngle - TRY_ROTATE_ANGLE);
                    rotation = -1;
                } else {
                    rotation = 1;
                }
            } else {
                direction = 1;
                rotation = 0;
            }
        }

        double scalar;

        // Поворот корпуса лбом к игроку
        scalar = scalarProd(normalizeVector(vecPlayer),
            Vector2f(cos(angle * PI / 180), sin(angle * PI / 180)));

        rotation = rotate(player.getPos(), angle);

        if (scalar > COS_30) {
            rotation = 0;
        }

        // Поворот башни на игрока
        rotateTurrel((Vector2i)player.getPos());

        /* Если угол между вектором направления башни врага
        и игроком меньше 10 градусов, а также если нет препятствий
        на пути, то можно стрелять */
        scalar = scalarProd(normalizeVector(vecPlayer),
            Vector2f(cos(dirTurrel * PI / 180), sin(dirTurrel * PI / 180)));

        if (scalar > COS_10) {
            bool canAimTo = true;

            for (std::list<GameObject*>::iterator it = objects.begin();
                it != objects.end(); ++it) {
                GameObject *obj = *it;
                if (collisionLineRect((IntRect)(*it)->getSprite().getGlobalBounds(), player.getPos())) {
                    canAimTo = false;
                    break;
                }
            }

            if (canAimTo == true) {
                fire(bullets, *texDynamicObjects);
            }
        }
        if (vectorLength(vecPlayer) < 200) {
            direction = 0;
        }
    }

    Tank::update(time, direction, rotation, objects, bullets, anims);

    for (std::list<Enemy*>::iterator it = enemies.begin();
        it != enemies.end(); ++it) {
        GameObject *obj = *it;
        if (*it != this) {
            while (checkCollision(obj)) {
                Tank::update(time, -direction, -rotation, objects, bullets, anims);
            }
        }
    }

    GameObject *objPlayer = &player;
    if (checkCollision(objPlayer) == true) {
        Tank::update(time, -direction, -rotation, objects, bullets, anims);
    }

    bigSprite.setPosition(position);
    bigSprite.setRotation(angle);
}

bool Enemy::isOutOfMap()
{
    Vector2f point;
    point.x = bigSprite.getPosition().x + bigSprite.getTextureRect().width *
        cos(bigSprite.getRotation() * PI / 180);
    point.y = bigSprite.getPosition().y + bigSprite.getTextureRect().width *
        sin(bigSprite.getRotation() * PI / 180);
    if (point.x > mapWidth || point.x < 0 ||
        point.y > mapHeight || point.y < 0) {
        return true;
    } else {
        return false;
    }
}

bool Enemy::collisionLineRect(IntRect rect, Vector2f playerPos)
{
    if ((getCode(rect, this->getPos()) & getCode(rect, playerPos)) == 0) {
        return true;
    } else {
        return false;
    }
}

int Enemy::getCode(IntRect rect, Vector2f point)
{
    if (point.x < rect.left) {
        if (point.y < rect.top) {
            return 9;
        }
        if ((point.y > rect.top) && (point.y < rect.top + rect.height)) {
            return 1;
        }
        if (point.y > rect.top + rect.height) {
            return 5;
        }
    }
    if ((point.x > rect.left) && (point.x < rect.left + rect.width)) {
        if (point.y < rect.top) {
            return 8;
        }
        if ((point.y > rect.top) && (point.y < rect.top + rect.height)) {
            return 0;
        }
        if (point.y > rect.top + rect.height) {
            return 4;
        }
    }
    if (point.x > rect.left + rect.width) {
        if (point.y < rect.top) {
            return 10;
        }
        if ((point.y > rect.top) && (point.y < rect.top + rect.height)) {
            return 2;
        }
        if (point.y > rect.top + rect.height) {
            return 6;
        }
    }

}

void Enemy::setAngle(double angle)
{
    this->angle = angle;
}

int Enemy::getHealth()
{
    return this->health;
}

void Enemy::setHealth(int health)
{
    this->health = health;
}

int Enemy::getDamageValue()
{
    return this->damage;
}

void Enemy::setDamageValue(int damage)
{
    this->damage = damage;
}