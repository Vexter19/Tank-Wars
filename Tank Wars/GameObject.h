#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include <list>
#include <cmath>
#include <sstream>
#include "global.h"
#include <SFML/Audio.hpp>

#define GERMANY 0
#define USSR 1
#define MAIN_FONT "fonts\\farcry4.otf"


using namespace sf;

double convertMeters(double meters);
double convertSpeed(double speed);

double sqr(double x);

double scalarProd(Vector2f a, Vector2f b);
double vectorLength(Vector2f a);
Vector2f normalizeVector(Vector2f a);

std::string numToStr(double number);

class GameObject
{
protected:
    Vector2f position;
    Texture texture;
    Sprite sprite;
    double speed;
    double angle;
    bool checkCollision(GameObject *obj);

public:
    GameObject(Vector2f pos, Texture &tex, IntRect rect);
    GameObject(Vector2f pos, std::string texPath, IntRect rect);

    Vector2f getPos();
    void setSpeed(double speed);
    void setAngle(double angle);
    Sprite getSprite();

    void draw(RenderWindow &window);
};



#endif // !GAMEOBJECT_H