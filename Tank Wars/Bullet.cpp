#include "Bullet.h"


Bullet::Bullet(std::list<Animation*> &anims, Vector2f pos, float angle,
    Texture *tex, IntRect rect, int damage) :
GameObject(pos, *tex, rect)
{
    texture = tex;
    this->angle = angle;
    sprite.setRotation(angle);
    this->damage = damage;
    speed = convertSpeed(BULLET_SPEED);
    dx = (speed) / 1000 * cos(angle * 3.14 / 180);
    dy = (speed) / 1000 * sin(angle * 3.14 / 180);
    life = true;

    anims.push_back(new Animation(*texture, 10, false, IntRect(0, 107, 45, 45),
        Vector2f(position.x, position.y)));
}

void Bullet::update(double time, View &view, RenderWindow &window,
    std::list<GameObject*> &objects, std::list<Animation*> &anims)
{
    position.x += dx * time;
    position.y += dy * time;

    if (((position.x > (view.getCenter().x + window.getSize().x)) ||
        (position.y > (view.getCenter().y + window.getSize().y))) ||
        (position.x < (view.getCenter().x - window.getSize().x)) ||
        (position.y < (view.getCenter().y - window.getSize().y))) {
        dx = 0;
        life = false;
    }

    for (std::list<GameObject*>::iterator it = objects.begin();
        it != objects.end(); ++it) {
        GameObject *obj = *it;
        if (checkCollision(obj) == true) {
            this->Destroy(anims);
        }
    }

    sprite.setPosition(position.x, position.y);  
}

bool Bullet::isAlive()
{
    return life;
}

void Bullet::Destroy(std::list<Animation*> &anims)
{
    life = false;

    if (graphicsSettings == LOW) {
        anims.push_back(new Animation(*texture, 13, false, IntRect(0, 10, 40, 40),
            Vector2f(position.x, position.y)));
    } else {
        anims.push_back(new Animation(*texture, 10, false, IntRect(5, 56, 40, 40),
            Vector2f(position.x, position.y)));
    }
}

int Bullet::getDmg()
{
    srand(this->angle * 100);
    double diffDamage = damage * ((rand() % (DAMAGE_SCATTER * 2)) -
        DAMAGE_SCATTER) / 100;
    return damage + diffDamage;
}