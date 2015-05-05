#include "Tank.h"


Tank::Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel,
    double rechargeTime, int damage, std::string name, int health) :
    GameObject(pos, tex, rect)
{
    dirTurrel = 0;
    this->speedOfRotation = speedOfRotation;
    this->maxSpeed = convertSpeed(maxSpeed);
    this->speedTurrel = speedTurrel;
    this->diffTankTurrel = diffTankTurrel;
    this->rechargeTime = rechargeTime;
    this->damage = damage;
    this->name = name;
    this->health = health;
    remainingTime = rechargeTime;
    this->life = true;

    spriteTurrel.setTexture(tex);
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
        Vector2f backupPos = position;

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

        // Считаем координаты центра башни.
        double xTur = position.x + diffTankTurrel * cos(angle * PI / 180);
        double yTur = position.y + diffTankTurrel * sin(angle * PI / 180);

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
            if (checkCollision(obj) == true) {
                backToPrevPos(direction, rotation, backupPos);
                if (rotation == 1) {
                    angle -= 1;
                } else if (rotation == -1) {
                    angle += 1;
                }
            }
        }

        // Обрабатываем выход за границы карты
        if (position.x >= mapWidth || position.x < 0 ||
            position.y >= mapHeight || position.y < 0) {
            backToPrevPos(direction, rotation, backupPos);
        }

        sprite.setPosition(position.x, position.y);
        spriteTurrel.setPosition(xTur, yTur);
        sprite.setRotation(angle);
    }
}

void Tank::rotateTurrel(Vector2i mouseVector)
{
    double dirMouse = (180 / PI * atan((mouseVector.y - position.y) /
        (mouseVector.x - position.x))); 
    if (mouseVector.x < position.x) {
        dirMouse += 180;
    } else if (mouseVector.y < position.y) {
        dirMouse += 360;
    }

    if (dirMouse >= 360) {
        dirMouse -= 360;
    }

    double dirDiff = dirMouse - dirTurrel;

    /*if ((dirTurrel <= 360 && dirTurrel >= 180)
        && (dirMouse >= 0 && dirMouse <= 90)) {
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

    if ((dirTurrel <= 361) && (dirTurrel >= 180)
        && (dirMouse >= 0) && (dirMouse <= 90)) {
        dirTurrel -= 360;
        sign = 1;
    }

    if ((dirMouse <= 361) && (dirMouse >= 180)
        && (dirTurrel >= 0) && (dirTurrel <= 90)) {
        dirTurrel += 360;
        sign = -1;
    }

    dirTurrel += sign * speedTurrel / 1000;
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
        double barrel = sprite.getTextureRect().width;
        gunVertex.x = position.x + barrel * cos(dirTurrel * PI / 180);
        gunVertex.y = position.y + barrel * sin(dirTurrel * PI / 180);
        bullets.push_back(new Bullet(gunVertex, dirTurrel, &texBullet, IntRect(0, 0, 17, 5), this->damage));
        remainingTime = rechargeTime;
    }
}

std::string Tank::getTankInfo()
{
    std::string strHealth;
    strHealth = numToStr(health);
    if (health > 0) {
        return (name + ", " + strHealth + "hp");
    } else {
        return (name);
    }
}

int Tank::getDamageOfBullet()
{
    return damage;
}

void Tank::getDamage(int damage)
{
    srand(time(0));

    // Рандомизация урона.
    double diff = damage * ((rand() % 20) - 10) / 100;

    int realDamage = damage + (int)diff;
    this->health -= realDamage;
}

bool Tank::isAlive()
{
    return life;
}

void Tank::backToPrevPos(int direction, int rotation, Vector2f backupPos)
{
    if (direction == 1) {
        position.x = backupPos.x -
            SPEED_OF_RETURNING * cos(angle * PI / 180);
        position.y = backupPos.y -
            SPEED_OF_RETURNING * sin(angle * PI / 180);
    } else if (direction == -1) {
        position.x = backupPos.x +
            SPEED_OF_RETURNING * cos(angle * PI / 180);
        position.y = backupPos.y +
            SPEED_OF_RETURNING * sin(angle * PI / 180);
    }
}