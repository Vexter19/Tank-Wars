#ifndef TANK_H
#define TANK_H
#include "GameObject.h"


using namespace sf;

const float PI = 3.14159265f;

class Tank :
    public GameObject
{
protected:
    //Tank
    double dx, dy;
    double speedOfRotation;
    double maxSpeed;
    //Turrel
    double dirTurrel;
    double speedTurrel;
    Sprite spriteTurrel;
public:
    //Tank
    Tank(Vector2f pos, Texture &tex, IntRect rect, IntRect rectTurrel, int turrelCenterX,
        double maxSpeed, double speedOfRotation, double speedTurrel);
    void update(double time, short int direction, short int rotation);
    void draw(RenderWindow &window);

    //Turrel 
    void rotateTurrel(Vector2i mousePos);
    double getTurrelDir();
};

#endif // !TANK_H