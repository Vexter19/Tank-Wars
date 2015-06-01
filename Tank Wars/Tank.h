#ifndef TANK_H
#define TANK_H
#include "GameObject.h"
#include "Bullet.h"
#include "View.h"
#include "TankCharacteristics.h"

#define SPEED_OF_RETURNING 10
#define MULTIPLIER 0.01
#define DIST_FROM_CORNER 10


extern const double mapWidth;
extern const double mapHeight;

using namespace sf;

const double PI = 3.14159265;

class Tank :
    public GameObject
{
private:
    int prevDir;
    Vector2f backupPos;
protected:
    //Tank
    Texture texTurrel;
    double dx, dy;
    double speedOfRotation;
    double maxSpeed;
    double diffTankTurrel; // –ассто€ние между центром танка и башни.
    double rechargeTime;
    double remainingTime; // ќставшеес€ врем€ до конца перезар€дки танка.
    int health;
    int damage;
    std::wstring name;
    bool life;

    void backToPrevPos(int direction, int rotation, float multiplier);
    int rotate(Vector2f point, double &dir);

    //Turrel
    double dirTurrel;
    double speedTurrel;
    Sprite spriteTurrel;
public:
    //Tank
    int maxHealth;

    Tank(Vector2f pos, std::string texPath, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel,
        double rechargeTime, int damage, std::wstring name, int health);

    void update(double time, short int direction, short int rotation,
        std::list<GameObject*> &objects, std::list<Bullet*> &bullets,
        std::list<Animation*> &anims);

    void draw(RenderWindow &window);
    void fire(std::list<Animation*> &anims, 
        std::list<Bullet*> &bullets, Texture &texBullet);
    void getDamage(int damage);

    std::wstring getTankName();
    std::wstring getTankInfo();
    int getDamageOfBullet();

    bool isAlive();

    //Turrel 
    void rotateTurrel(Vector2i mousePos, int rotation, int direction);
    double getTurrelDir();
    IntRect getTurrelRect();
};

#endif // !TANK_H