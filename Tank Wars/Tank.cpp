#include "Tank.h"
#include <iostream>


Tank::Tank(Vector2f pos, std::string texPath, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel,
    double rechargeTime, int damage, std::wstring name, int health) :
    GameObject(pos, texPath, rect)
{
    dirTurrel = 0;
    this->speedOfRotation = speedOfRotation;
    this->maxSpeed = convertSpeed(maxSpeed);
    this->speedTurrel = speedTurrel;
    this->diffTankTurrel = diffTankTurrel;
    this->rechargeTime = rechargeTime;
    this->damage = damage;
    this->name = name;
    this->maxHealth = health;
    this->health = health;
    this->remainingTime = rechargeTime;
    this->life = true;

    texTurrel.loadFromFile(texPath);
    spriteTurrel.setTexture(texTurrel);
    spriteTurrel.setTextureRect(rectTurrel);
    spriteTurrel.setOrigin(turrelCenterX, rectTurrel.height / 2);
}

void Tank::update(double time, short int direction, short int rotation,
    std::list<GameObject*> &objects, std::list<Bullet*> &bullets,
    std::list<Animation*> &anims)
{
    if (health < 0) {
        life = false;
    }
    if (life == true) {
        angle += speedOfRotation * rotation * time / 1000;
        speed = (direction > 0) ? (maxSpeed * direction) : (maxSpeed * direction / 2);

        dx = (speed) / 1000 * cos(angle * PI / 180);
        dy = (speed) / 1000 * sin(angle * PI / 180);

        position.x += dx * time;
        position.y += dy * time;

        speed = 0;

        if (remainingTime > 0) {
            remainingTime -= time / 1000;
        } else {
            remainingTime = 0;
        }

        

        // Обрабатываем столкновения с пулями...
        for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
            GameObject *obj_bullet = *it;
            if (checkCollision(obj_bullet) == true) {
                getDamage((*it)->getDmg());
                (*it)->Destroy(anims);
            }
        }

        // и с объектами на карте.
        for (std::list<GameObject*>::iterator it = objects.begin();
            it != objects.end(); ++it) {
            GameObject *obj = *it;
            while (checkCollision(obj) == true) {
                backToPrevPos(direction, rotation, MULTIPLIER);
            }
        }

        // Обрабатываем выход за границы карты
        if (position.x < 0) {
            position.x = 1;
        }
        if (position.x > mapWidth) {
            position.x = mapWidth - 1;
        }
        if (position.y < 0) {
            position.y = 1;
        }
        if (position.y > mapHeight) {
            position.y = mapHeight - 1;
        }

        // Считаем координаты центра башни.
        double xTur = position.x + diffTankTurrel * cos(angle * PI / 180);
        double yTur = position.y + diffTankTurrel * sin(angle * PI / 180);

        sprite.setPosition(position.x, position.y);
        spriteTurrel.setPosition(xTur, yTur);
        sprite.setRotation(angle);
    }
}

void Tank::rotateTurrel(Vector2i mouseVector, int rotation, int direction)
{
    if (direction == -1) {
        rotation *= -1;
    }
    dirTurrel += (rotate((Vector2f)mouseVector, dirTurrel) *
        speedTurrel + speedOfRotation * rotation)  / 100;
    spriteTurrel.setRotation(dirTurrel);
}

void Tank::draw(RenderWindow &window)
{
    if (life == true) {
        GameObject::draw(window);
        window.draw(spriteTurrel);
    }
}

double Tank::getTurrelDir()
{
    return dirTurrel;
}

IntRect Tank::getTurrelRect()
{
    return spriteTurrel.getTextureRect();
}

void Tank::fire(std::list<Bullet*> &bullets, Texture &texBullet)
{
    if (remainingTime == 0) {
        Vector2f gunVertex;
        // Длина дула танка. Чтобы пуля вылетала не из самого танка
        double barrel = sprite.getTextureRect().width;

        // Считаем координаты вершины орудия
        gunVertex.x = position.x + barrel * cos(dirTurrel * PI / 180);
        gunVertex.y = position.y + barrel * sin(dirTurrel * PI / 180);
        bullets.push_back(new Bullet(gunVertex, dirTurrel, &texBullet, IntRect(0, 0, 17, 5), this->damage));
        remainingTime = rechargeTime;

        soundShoot.play();
    }
}

std::wstring Tank::getTankInfo()
{
    std::string strHealth;
    strHealth = numToStr(health);
    if (health > 0) {
        return (name + ", " + strHealth + "hp");
    } else {
        return (name);
    }
}

std::wstring Tank::getTankName()
{
    return name;
}

int Tank::getDamageOfBullet()
{
    return damage;
}

void Tank::getDamage(int damage)
{
    this->health -= damage;
}

bool Tank::isAlive()
{
    return life;
}

void Tank::backToPrevPos(int direction, int rotation, float multiplier)
{
    // Если так случилось, что столкновение есть, а танк при этом не двигается
    if (direction == 0) {
        dx = cos(angle * PI / 180);
        dy = sin(angle * PI / 180);
        if (prevDir == -1) {
            dx *= -1;
            dy *= -1;
        }
    }

    rotation *= -1;

    position.x = position.x - dx * multiplier;
    position.y = position.y - dy * multiplier;

    if (position.x < -DIST_FROM_CORNER) {
        position.x = 0;
    }
    if (position.x > mapWidth + DIST_FROM_CORNER) {
        position.x = mapWidth;
    }
    if (position.y < -DIST_FROM_CORNER) {
        position.y = 0;
    }
    if (position.y > mapHeight + DIST_FROM_CORNER) {
        position.y = mapHeight;
    }

    sprite.setPosition(position.x - dx, position.y - dy);
    spriteTurrel.setPosition(position.x - dx, position.y - dy);

    if (direction != 0) {
        prevDir = direction;
    }
}

int Tank::rotate(Vector2f point, double &dir)
{
    double dirPoint = (180 / PI * atan((point.y - position.y) /
        (point.x - position.x)));
    if (point.x < position.x) {
        dirPoint += 180;
    } else if (point.y < position.y) {
        dirPoint += 360;
    }

    if (dirPoint >= 360) {
        dirPoint -= 360;
    }

    double dirDiff = dirPoint - dir;

    /*if ((dir <= 360 && dir >= 180)
    && (dirPoint >= 0 && dirPoint <= 90)) {
    dirDiff = -dirDiff;
    }*/

    int sign;
    if (dirDiff > 1) {
        sign = 1;
    } else if (dirDiff < -1) {
        sign = -1;
    } else {
        sign = 0;
    }

    if ((dir <= 361) && (dir >= 180)
        && (dirPoint >= 0) && (dirPoint <= 90)) {
        dir -= 360;
        sign = 1;
    }

    if ((dirPoint <= 361) && (dirPoint >= 180)
        && (dir >= 0) && (dir <= 90)) {
        dir += 360;
        sign = -1;
    }

    return sign;
}