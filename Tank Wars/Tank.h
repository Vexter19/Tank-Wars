#ifndef TANK_H
#define TANK_H
#include "GameObject.h"
#include "Bullet.h"

using namespace sf;

const double PI = 3.14159265;

class Tank :
    public GameObject
{
protected:
    //Tank
    double dx, dy;
    double speedOfRotation;
    double maxSpeed;
    double diffTankTurrel; // –ассто€ние между центром танка и башни.
    double rechargeTime;
    double remainingTime; // ќставшеес€ врем€ до конца перезар€дки танка.
    //Turrel
    double dirTurrel;
    double speedTurrel;
    Sprite spriteTurrel;
public:
    //Tank
    Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel, double rechargeTime);

    void update(double time, short int direction, short int rotation,
        std::list<Bullet*> &bullets, std::list<Animation*> &anims);

    void draw(RenderWindow &window);
    void Fire(std::list<Bullet*> &bullets, Texture &texBullet);

    //Turrel 
    void rotateTurrel(Vector2i mousePos);
    double getTurrelDir();
    IntRect getTurrelRect();
};

#endif // !TANK_H