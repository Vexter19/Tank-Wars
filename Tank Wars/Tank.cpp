#include "Tank.h"

Tank::Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, double rechargeTime) :
    GameObject(pos, tex, rect)
{
    dirTurrel = 0;
    this->speedOfRotation = speedOfRotation;
    this->maxSpeed = convertSpeed(maxSpeed);
    this->speedTurrel = speedTurrel;
    this->diffTankTurrel = diffTankTurrel;
    this->rechargeTime = rechargeTime;
    remainingTime = rechargeTime;

    spriteTurrel.setTexture(tex);
    spriteTurrel.setTextureRect(rectTurrel);
    spriteTurrel.setOrigin(turrelCenterX, rectTurrel.height / 2);
}

void Tank::update(double time, short int direction, short int rotation,
    std::list<Bullet*> &bullets, std::list<Animation*> &anims)
{
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

    // —читаем координаты центра башни.
    double xTur = position.x - diffTankTurrel * cos(angle * PI / 180);
    double yTur = position.y - diffTankTurrel * sin(angle * PI / 180);

    sprite.setPosition(xTur, yTur);
    spriteTurrel.setPosition(position.x, position.y);
    sprite.setRotation(angle);

    for (std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
        GameObject *obj_bullet = *it;
        if (checkCollision(obj_bullet) == true) {
            (*it)->Destroy(anims);
            
        }
    }
}

void Tank::rotateTurrel(Vector2i mouseVector)
{
    double dirMouse;
    if (mouseVector.x < position.x) {
        dirMouse = (180 / PI * atan((mouseVector.y - position.y) /
            (mouseVector.x - position.x))) + 180;
    } else {
        dirMouse = (180 / PI * atan((mouseVector.y - position.y) /
            (mouseVector.x - position.x)));
    }

    double dirDiff = dirMouse - dirTurrel;

    int sign;  
    if (dirDiff > 1) {
        sign = 1;
    } else if (dirDiff < -1) {
        sign = -1;
    } else {
        sign = 0;
    }

    
    dirTurrel += sign * speedTurrel / 1000;
    spriteTurrel.setRotation(dirTurrel);
}

void Tank::draw(RenderWindow &window)
{
    GameObject::draw(window);
    window.draw(spriteTurrel);
}

double Tank::getTurrelDir()
{
    return dirTurrel;
}

IntRect Tank::getTurrelRect()
{
    return spriteTurrel.getTextureRect();
}

void Tank::Fire(std::list<Bullet*> &bullets, Texture &texBullet)
{
    if (remainingTime == 0) {
        Vector2f gunVertex;
        double barrel = sprite.getTextureRect().width;
        gunVertex.x = position.x + barrel * cos(dirTurrel * PI / 180);
        gunVertex.y = position.y + barrel * sin(dirTurrel * PI / 180);
        bullets.push_back(new Bullet(gunVertex, dirTurrel, &texBullet, IntRect(0, 0, 17, 5)));
        remainingTime = rechargeTime;
    }
}