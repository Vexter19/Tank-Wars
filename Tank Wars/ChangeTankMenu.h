#ifndef CHANGETANKMENU_H
#define CHANGETANKMENU_H

#include "GameObject.h"
#include <list>
#include "TankCharacteristics.h"
#include "Player.h"
#include "MouseCursor.h"

#define PREV -1
#define NEXT 1


class TankTile
{
public:
    Texture* tex;
    int level;
    TankCharacteristic characteristic;

    TankTile(Texture* tex, int level, TankCharacteristic characteristic);
};

class ChangeTankMenu :
    public GameObject
{
private:
    int playerLevel;
    std::list<TankTile*> tanks;


    Texture texTank1;
    Texture texTank2;
    Texture texTank3;
    Texture texTank4;
    Texture texTank5;

    Sprite tank;
    Sprite arrowPrev;
    Sprite arrowNext;

    MouseCursor* mouse;
    // ������, ������� �������� ������������� 1�1 � ������� ��������� ����
    Sprite mousePoint;
public:
    ChangeTankMenu(int nation, Player &player, Texture &texGUI);
    bool run(Texture &texGUI, RenderWindow &window, Player &player);
    void draw(RenderWindow &window);
};

#endif // !CHANGETANKMENU_H



