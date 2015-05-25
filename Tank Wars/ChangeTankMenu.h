#pragma once
#include "GameObject.h"
#include <list>
#include "TankCharacteristics.h"
#include "Player.h"


struct TankTile
{
    Texture* tex;
    int level;
    TankCharacteristic* characteristics;
};

class ChangeTankMenu :
    public GameObject
{
private:
    std::list<TankTile*> tanks;

    Texture texTank1;
    Texture texTank2;
    Texture texTank3;
    Texture texTank4;
    Texture texTank5;

    Sprite tank;
    Sprite arrowPrev;
    Sprite arrowNext;
public:
    ChangeTankMenu(Vector2f pos, int nation, Player &player);
    void update();
    void draw();
};

