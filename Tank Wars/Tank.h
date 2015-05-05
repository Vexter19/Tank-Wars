#ifndef TANK_H
#define TANK_H
#include "GameObject.h"
#include "Bullet.h"
#include "View.h"

#define SPEED_OF_RETURNING 0.1

extern const double mapWidth;
extern const double mapHeight;

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
    int health;
    int damage;
    std::string name;
    bool life;

    void backToPrevPos(int direction, int rotation, Vector2f backupPos);

    //Turrel
    double dirTurrel;
    double speedTurrel;
    Sprite spriteTurrel;
public:
    //Tank
    Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel,
        double rechargeTime, int damage, std::string name, int health);

    void update(double time, short int direction, short int rotation,
        std::list<GameObject*> &objects, std::list<Bullet*> &bullets,
        std::list<Animation*> &anims);

    void draw(RenderWindow &window);
    void fire(std::list<Bullet*> &bullets, Texture &texBullet);
    void getDamage(int damage);

    std::string getTankInfo();
    int getDamageOfBullet();

    void setLife();
    bool isAlive();

    //Turrel 
    void rotateTurrel(Vector2i mousePos);
    double getTurrelDir();
    IntRect getTurrelRect();
};

#endif // !TANK_H