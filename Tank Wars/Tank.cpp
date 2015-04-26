#include "Tank.h"

Tank::Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel) :
    GameObject(pos, tex, rect)
{
    dirTurrel = 0;
    this->speedOfRotation = speedOfRotation;
    this->maxSpeed = convertSpeed(maxSpeed);
    this->speedTurrel = speedTurrel;
    this->diffTankTurrel = diffTankTurrel;

    spriteTurrel.setTexture(tex);
    spriteTurrel.setTextureRect(rectTurrel);
    spriteTurrel.setOrigin(turrelCenterX, rectTurrel.height / 2);
}

void Tank::update(double time, short int direction, short int rotation)
{
    angle += speedOfRotation * rotation * time / 1000;
    speed = (direction > 0) ? (maxSpeed * direction) : (maxSpeed * direction / 2);

    dx = (speed) / 1000 * cos(angle * PI / 180);
    dy = (speed) / 1000 * sin(angle * PI / 180);

    position.x += dx * time;
    position.y += dy * time;

    speed = 0;

    // —читаем координаты центра башни.
    double xTur = position.x - diffTankTurrel * cos(angle * PI / 180);
    double yTur = position.y - diffTankTurrel * sin(angle * PI / 180);

    sprite.setPosition(xTur, yTur);
    spriteTurrel.setPosition(position.x, position.y);
    sprite.setRotation(angle);
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