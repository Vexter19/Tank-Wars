#ifndef ENEMY_H
#define ENEMY_H
#include "Tank.h"
#include <cmath>
#include <iostream>

#define VISIBILITY 700
#define COS_10 0.98
#define COS_30 0.86
#define TRY_ROTATE_ANGLE 45
#define GO_DISTANCE 15
#define RAND_STOP_TIME 7

class Enemy :
    public Tank
{
private:
    Texture *texDynamicObjects;
    // Индикатор тревоги
    bool alert;
    // Расстояние, которое враг едет, будучи в спокойном состоянии
    double distance;
    // Расстояние, которое враг проехал, до того, как он захочет постоять
    double travelled;
    // Сохраняем направление, по которому врагу не получилось проехать, чтобы
    // не ехать так же ещё раз
    int prevRandDir;
    // Время, которое враг стоит на месте
    double stopTimeGone;
    double stopTime;
    // Точка, в которую враг будет вращать башню во время остановки
    Vector2f calmRotateTo1;
    Vector2f calmRotateTo2;
    double calmRotateAngle1;
    double calmRotateAngle2;
    // Хранит информацию о том, сколько раз враг уже вращал башней
    int rotated;

    bool isOutOfMap();
    bool collisionLineRect(IntRect rect, Vector2f playerPos);
    // Алгоритм Коэна-Сазерленда для определения пересечения
    // отрезка и прямоугольника
    int getCode(IntRect rect, Vector2f point);
public:
    double direction, rotation;
    Sprite bigSprite;

    Enemy(Vector2f pos, Texture *texDynObjs, TankCharacteristic tank);
    void update(double time, Tank &player, std::list<Bullet*> &bullets,
        std::list<GameObject*> &objects, std::list<Animation*> &anims);
    
    void setAngle(double angle);

    int getHealth();
    void setHealth(int helath);

    int getDamageValue();
    void setDamageValue(int damage);

    
};

#endif // !ENEMY_H