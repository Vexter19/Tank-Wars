#ifndef TANK_H
#define TANK_H
#include "GameObject.h"


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
    double diffTankTurrel; // Расстояние между центром танка и башни.
    //Turrel
    double dirTurrel;
    double speedTurrel;
    Sprite spriteTurrel;
public:
    //Tank
    Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel,
        int turrelCenterX, int diffTankTurrel, double maxSpeed,
        double speedOfRotation, double speedTurrel);
    void update(double time, short int direction, short int rotation);
    void draw(RenderWindow &window);

    //Turrel 
    void rotateTurrel(Vector2i mousePos);
    double getTurrelDir();
    IntRect getTurrelRect();
};

#endif // !TANK_H